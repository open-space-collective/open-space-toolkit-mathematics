# Open Space Toolkit ▸ Mathematics

[![Build Status](https://travis-ci.com/open-space-collective/open-space-toolkit-mathematics.svg?branch=master)](https://travis-ci.com/open-space-collective/open-space-toolkit-mathematics)
[![Code Coverage](https://codecov.io/gh/open-space-collective/open-space-toolkit-mathematics/branch/master/graph/badge.svg)](https://codecov.io/gh/open-space-collective/open-space-toolkit-mathematics)
[![Documentation](https://img.shields.io/readthedocs/pip/stable.svg)](https://open-space-collective.github.io/open-space-toolkit-mathematics)
[![GitHub version](https://badge.fury.io/gh/open-space-collective%2Fopen-space-toolkit-mathematics.svg)](https://badge.fury.io/gh/open-space-collective%2Fopen-space-toolkit-mathematics)
[![PyPI version](https://badge.fury.io/py/open-space-toolkit-mathematics.svg)](https://badge.fury.io/py/open-space-toolkit-mathematics)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Geometry, curve fitting, optimization.

## Warning

*⚠ This component is under development.*

## Installation

### C++

The binary packages are hosted using [GitHub Releases](https://github.com/open-space-collective/open-space-toolkit-mathematics/releases).

*Note: Don't forget to set the desired version number in the URLs!*

#### Debian / Ubuntu

```bash
# Download .deb packages

wget https://github.com/open-space-collective/open-space-toolkit-mathematics/releases/download/0.3.0/open-space-toolkit-mathematics-0.3.0-1.x86_64-runtime.deb
wget https://github.com/open-space-collective/open-space-toolkit-mathematics/releases/download/0.3.0/open-space-toolkit-mathematics-0.3.0-1.x86_64-devel.deb

# Install .deb packages

apt install -y open-space-toolkit-mathematics-0.3.0-*.deb
```

#### Fedora / CentOS

```bash
# Download .rpm packages

wget https://github.com/open-space-collective/open-space-toolkit-mathematics/releases/download/0.3.0/open-space-toolkit-mathematics-0.3.0-1.x86_64-runtime.rpm
wget https://github.com/open-space-collective/open-space-toolkit-mathematics/releases/download/0.3.0/open-space-toolkit-mathematics-0.3.0-1.x86_64-devel.rpm

# Install .rpm packages

dnf install -y open-space-toolkit-mathematics-0.3.0-*.rpm
```

### Python

The binary packages are hosted on [PyPI](https://pypi.org/project/open-space-toolkit-mathematics/):

```bash
pip install open-space-toolkit-mathematics
```

## Getting Started

Want to quickly get started? It's pretty simple.

Install [Docker](https://www.docker.com/) and try this:

```bash
docker run -it openspacecollective/open-space-toolkit-mathematics-python
```

This will start an [iPython](https://ipython.org/) shell within a container where the OSTk Mathematics component is already installed.

Once the shell is up and running, playing with it is easy:

```py
import numpy
from ostk.mathematics.geometry import Angle
from ostk.mathematics.geometry.d3.transformations.rotations import Quaternion
from ostk.mathematics.geometry.d3.transformations.rotations import RotationVector

rv = RotationVector(numpy.array([[0.0], [0.0], [1.0]], dtype=float), Angle.degrees(15.0)) # Construct rotation vector

q_AB = Quaternion(1.0, 2.0, 3.0, 4.0, Quaternion.Format.XYZS).to_normalized() # Construct quaternion and normalize
q_BC = Quaternion.rotation_vector(rv) # Construct quaternion from rotation vector

q_AC = q_AB * q_BC # Multiply quaternions
```

*Tip: Use tab for auto-completion!*

## Structure

The **Mathematics** library exhibits the following structure:

```txt
├── Objects
│   ├── Vector
│   ├── Matrix
│   └── Interval
├── Geometry
│   ├── 2D
|   │   ├── Objects
│   │   │   ├── Point
│   │   │   ├── Point Set
│   │   │   ├── Line
│   │   │   ├── Line String
│   │   │   ├── Multi Line String
│   │   │   └── Polygon
│   │   ├── Intersection
│   │   └── Transformations
│   │       ├── Identity
│   │       ├── Translation
│   │       ├── Rotation
│   │       ├── Reflection
│   │       ├── Scaling
│   │       └── Shear
│   ├── 3D
|   │   ├── Objects
│   │   │   ├── Point
│   │   │   ├── Point Set
│   │   │   ├── Line
│   │   │   ├── Ray
│   │   │   ├── Segment
│   │   │   ├── Line String
│   │   │   ├── Polygon
│   │   │   ├── Plane
│   │   │   ├── Cuboid
│   │   │   ├── Sphere
│   │   │   ├── Ellipsoid
│   │   │   ├── Cone
│   │   │   ├── Pyramid
│   │   │   └── Composite
│   │   ├── Intersection
│   │   └── Transformations
│   │       ├── Identity
│   │       ├── Translation
│   │       ├── Rotations
│   │       │   ├── Quaternion
│   │       │   ├── Euler Angle
│   │       │   ├── Rotation Vector
│   │       │   └── Rotation Matrix
│   │       ├── Reflection
│   │       ├── Scaling
│   │       └── Shear
├── Dynamics
│   ├── State
│   ├── Solvers
│   │   ├── Runge–Kutta 4 (RK4)
│   │   ├── Dormand–Prince 5 (DP5)
│   │   └── Runge–Kutta–Fehlberg 78 (F78)
│   └── Systems
├── Curve Fitting
│   ├── Interpolation
│   │   ├── Linear
│   │   ├── Cubic Spline
│   │   └── Lagrange
│   └── Smoothing
├── Optimization
│   ├── Problem
│   └── Algorithms
│       ├── Gradient Descent
│       └── Evolutionary
│           ├── Genetic
│           ├── Differential Evolution
│           └── Swarm
└── Statistics
```

## Documentation

Documentation is available here:

- [C++](https://open-space-collective.github.io/open-space-toolkit-mathematics)
- [Python](./bindings/python/docs)

## Tutorials

Tutorials are available here:

- [C++](./tutorials/cpp)
- [Python](./tutorials/python)

## Features

### Geometry Queries

- `○`: query only
- `✔`: query / intersection set
- ` `: to be implemented
- `-`: undefined

#### 3D

| Intersect        | Point | Point Set | Line | Ray | Segment | Line String | Polygon | Plane | Cuboid | Sphere | Ellipsoid | Cone | Pyramid | Composite |
|------------------|-------|-----------|------|-----|---------|-------------|---------|-------|--------|--------|-----------|------|---------|-----------|
| **Point**        |       |           | ○    | ○   |         |             |         | ✔     | ○      | ○      | ○         |      |         |           |
| **Point Set**    |       |           |      |     |         |             |         | ✔     | ○      | ○      | ○         |      |         |           |
| **Line**         | ○     |           |      |     |         |             |         | ✔     | ○      | ○      | ✔         |      |         |           |
| **Ray**          | ○     |           |      |     |         |             |         | ✔     |        | ○      | ✔         |      |         |           |
| **Segment**      |       |           |      |     |         |             |         | ✔     |        | ○      | ✔         |      |         |           |
| **Line String**  |       |           |      |     |         |             |         |       |        |        |           |      |         |           |
| **Polygon**      |       |           |      |     |         |             |         |       |        |        |           |      |         |           |
| **Plane**        | ✔     | ✔         | ✔    | ✔   | ✔       |             |         |       |        | ○      | ○         |      |         |           |
| **Cuboid**       | ○     | ○         | ○    |     |         |             |         |       |        |        |           |      |         |           |
| **Sphere**       | ○     | ○         | ○    | ○   | ○       |             |         | ○     |        |        |           |      | ○       |           |
| **Ellipsoid**    | ○     | ○         | ✔    | ✔   | ✔       |             |         | ○     |        |        |           | ✔    | ✔       |           |
| **Cone**         |       |           |      |     |         |             |         |       |        |        | ✔         |      |         |           |
| **Pyramid**      |       |           |      |     |         |             |         |       |        | ○      | ✔         |      |         |           |
| **Composite**    |       |           |      |     |         |             |         |       |        |        |           |      |         |           |

| Contain          | Point | Point Set | Line | Ray | Segment | Line String | Polygon | Plane | Cuboid | Sphere | Ellipsoid | Cone | Pyramid | Composite |
|------------------|-------|-----------|------|-----|---------|-------------|---------|-------|--------|--------|-----------|------|---------|-----------|
| **Point**        |       |           | -    | -   | -       | -           | -       | -     | -      | -      | -         | -    | -       |           |
| **Point Set**    |       |           | -    | -   | -       | -           | -       | -     | -      | -      | -         | -    | -       |           |
| **Line**         | ✔     |           |      |     |         |             | -       | -     | -      | -      | -         | -    | -       |           |
| **Ray**          | ✔     | ✔         | -    |     |         |             | -       | -     | -      | -      | -         | -    | -       |           |
| **Segment**      | ✔     |           | -    | -   |         |             | -       | -     | -      | -      | -         | -    | -       |           |
| **Line String**  |       |           | -    | -   |         |             | -       | -     | -      | -      | -         | -    | -       |           |
| **Polygon**      |       |           | -    | -   |         |             |         | -     | -      | -      | -         | -    | -       |           |
| **Plane**        | ✔     | ✔         | ✔    | ✔   | ✔       |             |         |       | -      | -      | -         | -    | -       |           |
| **Cuboid**       | ✔     | ✔         | -    | -   |         |             |         | -     |        |        |           |      |         |           |
| **Sphere**       | ✔     | ✔         | -    | -   | -       | -           | -       | -     |        |        |           |      |         |           |
| **Ellipsoid**    | ✔     | ✔         | -    | -   | -       | -           | -       | -     |        |        |           |      |         |           |
| **Cone**         |       |           |      |     |         | -           | -       | -     |        |        |           |      |         |           |
| **Pyramid**      | ✔     |           |      |     |         |             |         | -     |        |        |           |      |         |           |
| **Composite**    |       |           |      |     |         |             |         |       |        |        |           |      |         |           |

## Setup

### Development Environment

Using [Docker](https://www.docker.com) for development is recommended, to simplify the installation of the necessary build tools and dependencies.
Instructions on how to install Docker are available [here](https://docs.docker.com/install/).

To start the development environment:

```bash
make start-development
```

This will:

1. Build the `openspacecollective/open-space-toolkit-mathematics-development` Docker image.
2. Create a development environment container with local source files and helper scripts mounted.
3. Start a `bash` shell from the `./build` working directory.

If installing Docker is not an option, you can manually install the development tools (GCC, CMake) and all required dependencies,
by following a procedure similar to the one described in the [Development Dockerfile](./docker/development/Dockerfile).

### Build

From the `./build` directory:

```bash
cmake ..
make
```

*Tip: `helpers/build.sh` simplifies building from within the development environment.*

### Test

To start a container to build and run the tests:

```bash
make test
```

Or to run them manually:

```bash
./bin/open-space-toolkit-mathematics.test
```

*Tip: `helpers/test.sh` simplifies running tests from within the development environment.*

## Dependencies

| Name                   | Version | License                | Link                                                                                                   |
|------------------------|---------|------------------------|--------------------------------------------------------------------------------------------------------|
| Boost                  | 1.69.0  | Boost Software License | [boost.org](https://www.boost.org)                                                                     |
| Eigen                  | 3.3.7   | MPL2                   | [eigen.tuxfamily.org](http://eigen.tuxfamily.org/index.php)                                            |
| Geometric Tools Engine | 3.28    | Boost Software License | [geometrictools.com](https://www.geometrictools.com)                                                   |
| Core                   | master  | Apache License 2.0     | [github.com/open-space-collective/open-space-toolkit-core](https://github.com/open-space-collective/open-space-toolkit-core) |

## Contribution

Contributions are more than welcome!

Please read our [contributing guide](CONTRIBUTING.md) to learn about our development process, how to propose fixes and improvements, and how to build and test the code.

## Special Thanks

*To be completed...*

## License

Apache License 2.0
