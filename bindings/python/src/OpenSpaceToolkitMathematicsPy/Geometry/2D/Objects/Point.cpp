////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Point.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Point.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::ctnr::Array ;
using ostk::math::geom::d2::objects::Point ;
using ostk::math::obj::VectorXd ;

void                            set_point_array                             (   const   Array<Point>&               anArray                                     )
{

    (void) anArray ;

}

void                            set_point_2_array                           (   const   Array<Array<Point>>&        anArray                                     )
{

    (void) anArray ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Point  (  pybind11::module&       aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;

    class_<Point, Object>(aModule, "Point")

        .def(init<const Real&, const Real&>(), arg("x"), arg("y"))

        .def(self == self)
        .def(self != self)

        .def(self - self)

        .def(self + Vector2d())
        .def(self - Vector2d())

        .def("__str__", &(shiftToString<Point>))
        .def("__repr__", +[] (const Point& aPoint) -> std::string { return aPoint.toString() ; })

        .def("is_defined", &Point::isDefined)
        .def("is_near", &Point::isNear, arg("point"), arg("tolerance"))

        .def("x", &Point::x, return_value_policy::reference)
        .def("y", &Point::y, return_value_policy::reference)
        .def("as_vector", &Point::asVector)
        .def("distance_to", &Point::distanceTo, arg("point"))
        .def("to_string", &Point::toString, "aFormat"_a=Object::Format::Standard, "aPrecision"_a=Integer::Undefined())
        .def("apply_transformation", &Point::applyTransformation, arg("transformation"))

        .def_static("undefined", &Point::Undefined)
        .def_static("origin", &Point::Origin)
        .def_static("vector", &Point::Vector, arg("vector"))

    ;

    // implicitly_convertible<Point, Vector2d>() ;
    // implicitly_convertible<Vector2d, Point>() ;

    aModule.def("set_point_array", overload_cast<const Array<Point>&>(&set_point_array));
    aModule.def("set_point_2_array", overload_cast<const Array<Array<Point>>&>(&set_point_2_array));

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
