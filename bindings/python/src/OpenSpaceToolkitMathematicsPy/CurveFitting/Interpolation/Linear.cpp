////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolation/Linear.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolation/Linear.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolation_Linear ( pybind11::module& aModule                                     )
{

    using namespace pybind11 ;

    using ostk::math::curvefitting::interp::LinearInterpolator ;

    // noncopyable class with Boost, removed in Pybind11
    class_<LinearInterpolator>(aModule, "LinearInterpolator")

        .def(init<const VectorXd&, const VectorXd&>(), arg("x"), arg("y"))

        .def("evaluate", overload_cast<const VectorXd&>(&LinearInterpolator::evaluate, const_), arg("x"))
        .def("evaluate", overload_cast<const double&>(&LinearInterpolator::evaluate, const_), arg("x"))
    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
