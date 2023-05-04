////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolator/CubicSpline.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CubicSpline.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_CubicSpline ( pybind11::module& aModule                                )
{

    using namespace pybind11 ;

    using ostk::core::types::Real ;
    using ostk::math::obj::VectorXd ;

    using ostk::math::curvefitting::interp::CubicSpline ;

    // noncopyable class with Boost, removed in Pybind11
    class_<CubicSpline>(aModule, "CubicSpline")

        .def(init<const VectorXd&, const VectorXd&>(), arg("x"), arg("y"))
        .def(init<const VectorXd&, const Real&, const Real&>(), arg("y"), arg("x_0"), arg("h"))

        .def("evaluate", overload_cast<const VectorXd&>(&CubicSpline::evaluate, const_), arg("x"))
        .def("evaluate", overload_cast<const double&>(&CubicSpline::evaluate, const_), arg("x"))
    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
