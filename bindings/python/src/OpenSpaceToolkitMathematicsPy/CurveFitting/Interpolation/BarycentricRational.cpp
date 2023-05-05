////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolation/BarycentricRational.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolation/BarycentricRational.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolation_BarycentricRational ( pybind11::module& aModule                        )
{

    using namespace pybind11 ;

    using ostk::math::curvefitting::interp::BarycentricRational ;

    // noncopyable class with Boost, removed in Pybind11
    class_<BarycentricRational>(aModule, "BarycentricRational")

        .def(init<const VectorXd&, const VectorXd&>(), arg("x"), arg("y"))

        .def("evaluate", overload_cast<const VectorXd&>(&BarycentricRational::evaluate, const_), arg("x"))
        .def("evaluate", overload_cast<const double&>(&BarycentricRational::evaluate, const_), arg("x"))
    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////