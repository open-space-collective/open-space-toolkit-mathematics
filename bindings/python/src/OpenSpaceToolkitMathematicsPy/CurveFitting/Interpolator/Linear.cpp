////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolator/Linear.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/Linear.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_Linear ( pybind11::module& aModule                                      )
{

    using namespace pybind11 ;

    using ostk::math::curvefitting::interp::Linear ;

    // noncopyable class with Boost, removed in Pybind11
    class_<Linear>(aModule, "Linear")

        .def(init<const VectorXd&, const VectorXd&>(), arg("x"), arg("y"))

        .def("evaluate", overload_cast<const VectorXd&>(&Linear::evaluate, const_), arg("x"))
        .def("evaluate", overload_cast<const double&>(&Linear::evaluate, const_), arg("x"))
    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////