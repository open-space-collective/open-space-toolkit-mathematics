Library ▸ Mathematics
=====================

Geometry, curve fitting, optimization.

[![Build Status](https://travis-ci.com/open-space-collective/library-mathematics.svg?branch=master)](https://travis-ci.com/open-space-collective/library-mathematics)
[![Code Coverage](https://codecov.io/gh/open-space-collective/library-mathematics/branch/master/graph/badge.svg)](https://codecov.io/gh/open-space-collective/library-mathematics)
[![Documentation](https://img.shields.io/readthedocs/pip/stable.svg)](https://open-space-collective.github.io/library-mathematics)

## Warning

Library **name** and **license** are yet to be defined.

Please check the following projects:

- [Naming Project](https://github.com/orgs/open-space-collective/projects/1)
- [Licensing Project](https://github.com/orgs/open-space-collective/projects/2)

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
│   │   │   ├── Rectangle
│   │   │   ├── Plane
│   │   │   ├── Sphere
│   │   │   ├── Ellipsoid
│   │   │   ├── Cone
│   │   │   └── Pyramid
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

The documentation can be found [here](https://open-space-collective.github.io/library-mathematics).

## Setup

### Development

Using [Docker](https://www.docker.com) is recommended, as the development tools and dependencies setup is described in the provided [Dockerfile](./tools/development/docker/Dockerfile).

Instructions to install Docker can be found [here](https://docs.docker.com/install/).

Start the development environment:

```bash
./tools/development/start.sh
```

This will also build the `openspacecollective/library-mathematics:latest` Docker image, if not present already.

If installing Docker is not an option, please manually install the development tools (GCC, CMake) and the dependencies.
The procedure should be similar to the one described in the [Dockerfile](./tools/development/docker/Dockerfile).

### Build

From the development environment:

```bash
./build.sh
```

Manually:

```bash
mkdir -p build
cd build
cmake ..
make
```

### Test

From the development environment:

```bash
./test.sh
```

Manually:

```bash
./bin/library-mathematics.test
```

## Dependencies

The **Mathematics** library internally uses the following dependencies:

| Name                   | Version | License                | Link                                                                                                   |
|------------------------|---------|------------------------|--------------------------------------------------------------------------------------------------------|
| Boost                  | 1.67.0  | Boost Software License | [boost.org](https://www.boost.org)                                                                     |
| Eigen                  | 3.3.4   | MPL2                   | [eigen.tuxfamily.org](http://eigen.tuxfamily.org/index.php)                                            |
| Geometric Tools Engine | 3.14    | Boost Software License | [geometrictools.com](https://www.geometrictools.com)                                                   |
| Core                   | master  | TBD                    | [github.com/open-space-collective/library-core](https://github.com/open-space-collective/library-core) |

## Contribution

Contributions are more than welcome!

Please read our [contributing guide](CONTRIBUTING.md) to learn about our development process, how to propose fixes and improvements, and how to build and test the code.

## Special Thanks

*To be completed...*

## License

*To be defined...*