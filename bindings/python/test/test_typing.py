# Apache License 2.0

"""Calls that the bindings accept, and that the generated type stubs must accept too.

The bindings convert some Python values implicitly, for example a list of floats where a
vector is declared. Each test makes such a call. `test_stubs_accept_these_calls` type-checks
this file with mypy against the generated stubs, so a stub that rejects one of these calls
fails.
"""

from pathlib import Path

import numpy as np
import pytest

import ostk.mathematics
from ostk.mathematics.curve_fitting.interpolator import Linear
from ostk.mathematics.geometry.d3.object import Point
from ostk.mathematics.geometry.d3.transformation.rotation import Quaternion
from ostk.mathematics.geometry.d3.transformation.rotation import RotationMatrix


def test_vector_parameter_accepts_list() -> None:
    point: Point = Point.vector([1.0, 2.0, 3.0])
    vector: np.ndarray = point.as_vector()

    assert vector.tolist() == [1.0, 2.0, 3.0]


def test_vector_parameter_accepts_tuple() -> None:
    assert Point.vector((1.0, 2.0, 3.0)) == Point(1.0, 2.0, 3.0)


def test_dynamic_vector_parameters_accept_lists() -> None:
    interpolator = Linear([0.0, 1.0], [0.0, 2.0])

    assert interpolator.evaluate(0.5) == pytest.approx(1.0)


def test_matrix_parameter_accepts_nested_lists() -> None:
    rotation_matrix = RotationMatrix([[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]])
    matrix: np.ndarray = rotation_matrix.get_matrix()

    assert matrix.tolist() == [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]


def test_string_parameter_accepts_str() -> None:
    quaternion = Quaternion.parse("[0.0, 0.0, 0.0, 1.0]", Quaternion.Format.XYZS)

    assert quaternion.is_unitary()


def test_stubs_accept_these_calls(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    mypy_api = pytest.importorskip("mypy.api")

    # In the CMake build tree, the package is a directory next to `test`, not an installed
    # distribution: mypy only finds it through MYPYPATH.
    package_root: Path = Path(ostk.mathematics.__file__).resolve().parents[2]

    if package_root.name != "site-packages":
        monkeypatch.setenv("MYPYPATH", str(package_root))

    # Report the errors in the calls of this file only: the stubs themselves are not checked,
    # as for an installed package.
    config: Path = tmp_path / "mypy.ini"
    config.write_text("[mypy]\n[mypy-ostk.*]\nignore_errors = True\n")

    stdout, stderr, exit_status = mypy_api.run(
        [
            __file__,
            "--config-file",
            str(config),
            "--cache-dir",
            str(tmp_path / "mypy_cache"),
        ]
    )

    assert exit_status == 0, stdout + stderr
