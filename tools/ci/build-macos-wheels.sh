#!/usr/bin/env bash

# Apache License 2.0

# Build Apple Silicon wheels for open-space-toolkit-mathematics.
# fmt, Eigen, and Geometric Tools are installed with tools/dependencies, as in
# docker/development/Dockerfile.
# Core is built from the branch that can produce macOS libraries. Released Core
# packages are Linux debs, which this host cannot install.
# Homebrew Boost is linked dynamically and vendored with delocate.

set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
prefix="${root}/.macos-deps"
build_dir="${root}/build-macos"
packages_dir="${root}/packages/python"
core_ref="${OSTK_CORE_REF:-users/lucas/build-package-python-macos-arm}"
sibling="$(cd "${root}/../open-space-toolkit-core" 2>/dev/null && pwd || true)"
if [[ -n "${OSTK_CORE_SRC:-}" ]]; then
    core_src="${OSTK_CORE_SRC}"
elif [[ -x "${sibling}/tools/ci/build-macos-wheels.sh" ]]; then
    core_src="${sibling}"
else
    core_src="${prefix}/src/open-space-toolkit-core"
fi

export HOMEBREW_NO_AUTO_UPDATE=1
export NONINTERACTIVE=1
# Homebrew Python links extensions with a bare `clang -bundle`, which fails on the source-less _platform extension.
export UV_PYTHON_PREFERENCE=only-managed
unset VIRTUAL_ENV

if [[ "$(uname -s)" != "Darwin" ]]; then
    echo "macOS wheels must be built on Darwin."
    exit 1
fi

if [[ "$(uname -m)" != "arm64" ]]; then
    echo "This script builds Apple Silicon (arm64) wheels. The current machine is $(uname -m)."
    exit 1
fi

if ! command -v brew >/dev/null 2>&1; then
    echo "Homebrew is required."
    exit 1
fi

export PATH="$(brew --prefix)/bin:${HOME}/.local/bin:${PATH}"

if ! command -v uv >/dev/null 2>&1; then
    curl -LsSf https://astral.sh/uv/install.sh | sh
    export PATH="${HOME}/.local/bin:${PATH}"
fi

brew install cmake boost

deployment_target="${MACOSX_DEPLOYMENT_TARGET:-14.0}"
boost_library="$(find "$(brew --prefix boost)/lib" -name 'libboost_filesystem.dylib' -print -quit)"
if [[ -f "${boost_library}" ]]; then
    library_minos="$(otool -l "${boost_library}" | awk '/minos/ { print $2; exit }')"
    if [[ -n "${library_minos}" ]]; then
        deployment_target="$(
            deployment_target="${deployment_target}" library_minos="${library_minos}" python3 - <<'PY'
import os

def version(value):
    return tuple(int(part) for part in value.split("."))

chosen = os.environ["deployment_target"]
required = os.environ["library_minos"]
print(required if version(required) > version(chosen) else chosen)
PY
        )"
    fi
fi
if [[ "${deployment_target}" != "${MACOSX_DEPLOYMENT_TARGET:-14.0}" ]]; then
    echo "Homebrew Boost requires macOS ${deployment_target}. The wheel deployment target is ${deployment_target}."
fi
export MACOSX_DEPLOYMENT_TARGET="${deployment_target}"
# CMake 4 dropped compatibility with projects that declare cmake_minimum_required below 3.5.
export CMAKE_POLICY_VERSION_MINIMUM=3.5

if [[ ! -f "${prefix}/.installed" ]]; then
    INSTALL_PREFIX="${prefix}" "${root}/tools/dependencies/install.sh"
    touch "${prefix}/.installed"
fi

# A full branch clone is required so git describe can see the 5.x tag.
# A depth-1 clone falls back to a date version, which Mathematics rejects.
if [[ "${core_src}" == "${prefix}/src/open-space-toolkit-core" ]]; then
    if [[ -d "${core_src}/.git" ]] && ! git -C "${core_src}" describe --tags --match '5.*' --always | grep -q '^5\.'; then
        rm -rf "${core_src}"
    fi
    if [[ ! -d "${core_src}/.git" ]]; then
        git clone --single-branch --branch "${core_ref}" https://github.com/open-space-collective/open-space-toolkit-core.git "${core_src}"
    fi
fi

shopt -s nullglob
core_wheels=("${core_src}/packages/python/"*cp314-cp314-*.whl)
if [[ ${#core_wheels[@]} -eq 0 ]]; then
    bash "${core_src}/tools/ci/build-macos-wheels.sh"
    core_wheels=("${core_src}/packages/python/"*cp314-cp314-*.whl)
fi
if [[ ${#core_wheels[@]} -eq 0 ]]; then
    echo "Core did not produce a CPython 3.14 wheel."
    exit 1
fi

# Install headers, including the .tpp files, into the same layout as the Core deb.
cmake --install "${core_src}/build-macos" --prefix "${prefix}"
core_library="${prefix}/lib/libopen-space-toolkit-core.dylib"
if [[ ! -f "${core_library}" ]]; then
    echo "Core did not install libopen-space-toolkit-core.dylib."
    exit 1
fi

tool_venv="${prefix}/tool-venv"
if [[ ! -x "${tool_venv}/bin/python" ]]; then
    uv venv "${tool_venv}" --python 3.12
fi
uv pip install --python "${tool_venv}/bin/python" "pybind11>=2.12" delocate
pybind11_dir="$("${tool_venv}/bin/python" -c 'import pybind11; print(pybind11.get_cmake_dir())')"

installed_versions=()
for version in 3.9 3.10 3.11 3.12 3.13 3.14; do
    if uv python install "${version}"; then
        installed_versions+=("${version}")
    elif [[ "${version}" == "3.9" ]]; then
        echo "Python 3.9 has no build for this macOS. Skipping it."
    else
        echo "Failed to install Python ${version}."
        exit 1
    fi
done

python_search_versions="$(IFS=';'; echo "${installed_versions[*]}")"

# The published Core wheels are Linux-only. uv sync must use the wheels this script just built.
export UV_FIND_LINKS="${core_src}/packages/python"
export CPATH="${prefix}/include:${core_src}/.macos-deps/include${CPATH:+:${CPATH}}"

rm -rf "${build_dir}"
cmake -S "${root}" -B "${build_dir}" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_PREFIX_PATH="${prefix};${core_src}/.macos-deps;$(brew --prefix)" \
    -DCMAKE_OSX_DEPLOYMENT_TARGET="${MACOSX_DEPLOYMENT_TARGET}" \
    -DGTE_ROOT_DIR="${prefix}" \
    -DOpenSpaceToolkitCore_DIR="${prefix}/lib/cmake/OpenSpaceToolkitCore" \
    -DOpenSpaceToolkitCore_INCLUDE_DIR="${prefix}/include" \
    -DOpenSpaceToolkitCore_LIBRARY="${core_library}" \
    -Dpybind11_DIR="${pybind11_dir}" \
    -DPYTHON_SEARCH_VERSIONS="${python_search_versions}" \
    -DBUILD_WITH_DEBUG_SYMBOLS=OFF \
    -DBUILD_UNIT_TESTS=OFF \
    -DBUILD_PYTHON_BINDINGS=ON \
    -DBUILD_DOCUMENTATION=OFF \
    -DBUILD_WITH_BOOST_STACKTRACE=OFF \
    -DBUILD_WITH_BOOST_STATIC=OFF
cmake --build "${build_dir}" --parallel "$(sysctl -n hw.ncpu)"

mkdir -p "${packages_dir}"
rm -f "${packages_dir}"/*.whl
wheels=("${build_dir}/bindings/python/dist/"*.whl)
if [[ ${#wheels[@]} -eq 0 ]]; then
    echo "CMake did not produce any wheels."
    exit 1
fi

for wheel in "${wheels[@]}"; do
    # Core stays in the open-space-toolkit-core wheel. delocate cannot see that copy while packing this one.
    "${tool_venv}/bin/delocate-wheel" --require-archs arm64 --ignore-missing-dependencies -w "${packages_dir}" "${wheel}"
done

for wheel in "${packages_dir}"/*.whl; do
    unpack="$(mktemp -d)"
    unzip -q "${wheel}" -d "${unpack}"
    for binary in "${unpack}"/ostk/mathematics/libopen-space-toolkit-mathematics*.dylib "${unpack}"/ostk/mathematics/OpenSpaceToolkitMathematicsPy*.so; do
        [[ -f "${binary}" ]] || continue
        install_name_tool -add_rpath @loader_path/../core "${binary}"
        codesign -s - -f "${binary}" >/dev/null
    done
    rm -f "${wheel}"
    uv run --python 3.12 --with wheel wheel pack "${unpack}" -d "${packages_dir}" >/dev/null
    rm -rf "${unpack}"
done

for wheel in "${packages_dir}"/*.whl; do
    dependencies="$("${tool_venv}/bin/delocate-listdeps" --all "${wheel}" || true)"
    if grep -E '/opt/homebrew|/usr/local|/.macos-deps/|open-space-toolkit-core/lib/' <<<"${dependencies}"; then
        echo "Wheel still depends on libraries outside the archive: ${wheel}"
        echo "${dependencies}"
        exit 1
    fi
done

smoke_wheel="$(echo "${packages_dir}"/*cp314-cp314-*.whl)"
smoke_venv="${prefix}/smoke-venv"
rm -rf "${smoke_venv}"
uv venv "${smoke_venv}" --python 3.14
uv pip install --python "${smoke_venv}/bin/python" "${core_wheels[0]}" "${smoke_wheel}"
"${smoke_venv}/bin/python" -c 'import ostk.mathematics'

echo "macOS wheels are in ${packages_dir}"
