# Open Space Toolkit ▸ Mathematics

Geometry, curve fitting, optimization.

[![Build Status](https://travis-ci.com/open-space-collective/library-mathematics.svg?branch=master)](https://travis-ci.com/open-space-collective/library-mathematics)
[![Code Coverage](https://codecov.io/gh/open-space-collective/library-mathematics/branch/master/graph/badge.svg)](https://codecov.io/gh/open-space-collective/library-mathematics)
[![Documentation](https://img.shields.io/readthedocs/pip/stable.svg)](https://open-space-collective.github.io/library-mathematics)
[![GitHub version](https://badge.fury.io/gh/open-space-collective%2Flibrary-mathematics.svg)](https://badge.fury.io/gh/open-space-collective%2Flibrary-mathematics)
[![PyPI version](https://badge.fury.io/py/LibraryMathematicsPy.svg)](https://badge.fury.io/py/LibraryMathematicsPy)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

## Warning

Library **name** is yet to be defined.

Please check the following projects:

- [Naming Project](https://github.com/orgs/open-space-collective/projects/1)

*⚠ This library is still under heavy development. Do not use!*

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

- [C++](https://open-space-collective.github.io/library-io)
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

1. Build the `openspacecollective/library-mathematics-development` Docker image.
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
./bin/library-mathematics.test
```

*Tip: `helpers/test.sh` simplifies running tests from within the development environment.*

## Dependencies

| Name                   | Version | License                | Link                                                                                                   |
|------------------------|---------|------------------------|--------------------------------------------------------------------------------------------------------|
| Boost                  | 1.69.0  | Boost Software License | [boost.org](https://www.boost.org)                                                                     |
| Eigen                  | 3.3.7   | MPL2                   | [eigen.tuxfamily.org](http://eigen.tuxfamily.org/index.php)                                            |
| Geometric Tools Engine | 3.28    | Boost Software License | [geometrictools.com](https://www.geometrictools.com)                                                   |
| Core                   | master  | Apache License 2.0     | [github.com/open-space-collective/library-core](https://github.com/open-space-collective/library-core) |

## Contribution

Contributions are more than welcome!

Please read our [contributing guide](CONTRIBUTING.md) to learn about our development process, how to propose fixes and improvements, and how to build and test the code.

## Special Thanks

*To be completed...*

## License

Apache License 2.0
