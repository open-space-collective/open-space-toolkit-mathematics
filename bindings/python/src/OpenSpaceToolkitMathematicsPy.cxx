/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Utility/ArrayCasting.hpp>
#include <OpenSpaceToolkitMathematicsPy/Utility/EigenSequenceCasting.hpp>
#include <OpenSpaceToolkitMathematicsPy/Utility/ShiftToString.hpp>
#include <nanobind/eigen/dense.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/complex.h>
#include <nanobind/stl/function.h>
#include <nanobind/stl/map.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/pair.h>
#include <nanobind/stl/set.h>
#include <nanobind/stl/shared_ptr.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/unique_ptr.h>
#include <nanobind/stl/unordered_map.h>
#include <nanobind/stl/unordered_set.h>
#include <nanobind/stl/vector.h>

#include <OpenSpaceToolkitMathematicsPy/CurveFitting.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry.cpp>
#include <OpenSpaceToolkitMathematicsPy/Object.cpp>
#include <OpenSpaceToolkitMathematicsPy/Solver.cpp>

NB_MODULE(OpenSpaceToolkitMathematicsPy, m)
{
    // Add optional docstring for package OpenSpaceToolkitMathematicsPy
    m.doc() = "Geometry, curve fitting, optimization for OpenSpaceToolkit";

    // Change attribute __name__ to make OpenSpaceToolkitMathematicsPy invisible in modules path
    m.attr("__name__") = "ostk.mathematics";

// Package version information
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

    // Add python submodules to OpenSpaceToolkitMathematicsPy
    OpenSpaceToolkitMathematicsPy_Object(m);
    OpenSpaceToolkitMathematicsPy_Geometry(m);
    OpenSpaceToolkitMathematicsPy_CurveFitting(m);
    OpenSpaceToolkitMathematicsPy_Solver(m);
}
