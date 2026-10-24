#!/usr/bin/env bash

# Apache License 2.0

# Install Geometric Tools Engine headers into ${INSTALL_PREFIX}/include/Gte.

set -euo pipefail

GEOMETRIC_TOOLS_ENGINE_VERSION="3.28"
prefix="${INSTALL_PREFIX:-/usr/local}"

source_dir="$(mktemp -d)"
trap 'rm -rf "${source_dir}"' EXIT

git clone --branch "${GEOMETRIC_TOOLS_ENGINE_VERSION}" --depth 1 https://github.com/lucas-bremond/geometric-tools-engine.git "${source_dir}"

mkdir -p "${prefix}/include"
cp -R "${source_dir}/Include" "${prefix}/include/Gte"
