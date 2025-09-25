# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build and Development Commands

### Standard Development
- `make start-development`: Start the development environment in Docker
- `make test`: Run all tests (unit tests + coverage)
- `make test-unit-cpp`: Run C++ unit tests only
- `make test-unit-python`: Run Python unit tests only
- `make format`: Format C++ and Python code
- `make format-check`: Check code formatting without modifying files

### Advanced Development
- `make start-development-link links="/path/to/dependency"`: Start development with linked dependencies
- `make build-packages`: Build C++ and Python packages
- `make clean`: Clean build artifacts

### From Build Directory
When inside the Docker development environment (`/app/build/`):
- `cmake ..`: Configure build
- `make -j 4`: Build in parallel
- `make test`: Run tests
- `./bin/open-space-toolkit-mathematics.test`: Run specific test executable

### Testing Single Components
- Tests follow Google Test framework
- Test files are located in `test/OpenSpaceToolkit/Mathematics/`
- Use `--gtest_filter=TestSuiteName.TestName` to run specific tests

## Code Architecture

### Module Structure
The library is organized under `OpenSpaceToolkit::Mathematics` namespace with these main modules:

1. **Object** (`src/OpenSpaceToolkit/Mathematics/Object/`):
   - Basic mathematical objects: Vector, Matrix, Interval

2. **Geometry** (`src/OpenSpaceToolkit/Mathematics/Geometry/`):
   - **2D**: Points, Lines, Polygons, Transformations
   - **3D**: Points, Lines, Rays, Segments, Planes, 3D shapes (Sphere, Ellipsoid, Cone, etc.)
   - Intersection algorithms and geometric queries

3. **CurveFitting** (`src/OpenSpaceToolkit/Mathematics/CurveFitting/`):
   - Interpolators: Linear, BarycentricRational, CubicSpline

4. **Solver** (`src/OpenSpaceToolkit/Mathematics/Solver/`):
   - NumericalSolver for differential equations

### File Organization
- **Headers**: `include/OpenSpaceToolkit/Mathematics/`
- **Source**: `src/OpenSpaceToolkit/Mathematics/`
- **Tests**: `test/OpenSpaceToolkit/Mathematics/`
- **Python Bindings**: `bindings/python/`

### Dependencies
- **Open Space Toolkit Core** (v5.x): Base framework
- **Eigen3**: Linear algebra library
- **Geometric Tools Engine**: Advanced geometric computations
- **Boost** (v1.82): Utilities and stacktrace support
- **Google Test**: Testing framework

## Development Workflow

### Docker-based Development
This project uses Docker containers for consistent development environments. The development image includes all dependencies and development tools.

### Code Style
- Uses `.clang-format` for C++ formatting
- Python formatting via `black`
- Format checking is enforced in CI

### CMake Configuration
Key CMake options:
- `BUILD_UNIT_TESTS`: Enable/disable unit tests (default: ON)
- `BUILD_PYTHON_BINDINGS`: Enable Python bindings (default: ON)
- `BUILD_WITH_DEBUG_SYMBOLS`: Include debug symbols (default: ON)
- `BUILD_CODE_COVERAGE`: Enable coverage reporting

### Python Integration
- Python bindings are built using pybind11
- Package structure: `ostk.mathematics`
- Tests use pytest framework

## Common Tasks

### Adding New Geometric Objects
1. Add header in `include/OpenSpaceToolkit/Mathematics/Geometry/[2D|3D]/Object/`
2. Implement in `src/OpenSpaceToolkit/Mathematics/Geometry/[2D|3D]/Object/`
3. Add tests in `test/OpenSpaceToolkit/Mathematics/Geometry/[2D|3D]/Object/`
4. Update intersection tables and containment logic if applicable

### Running Specific Tests
```bash
# In development container
./bin/open-space-toolkit-mathematics.test --gtest_filter="GeometryTest*"
```

### Building Documentation
```bash
make build-documentation
```

### Code Coverage
```bash
make test-coverage-cpp
# Results available in coverage/ directory
```