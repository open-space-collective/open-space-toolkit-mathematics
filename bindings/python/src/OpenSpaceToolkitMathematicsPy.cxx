/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Utility/ArrayCasting.hpp>
#include <OpenSpaceToolkitMathematicsPy/Utility/ShiftToString.hpp>
#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <OpenSpaceToolkitMathematicsPy/CurveFitting.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry.cpp>
#include <OpenSpaceToolkitMathematicsPy/Object.cpp>
#include <OpenSpaceToolkitMathematicsPy/Solver.cpp>

PYBIND11_MODULE(OpenSpaceToolkitMathematicsPy, m)
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
