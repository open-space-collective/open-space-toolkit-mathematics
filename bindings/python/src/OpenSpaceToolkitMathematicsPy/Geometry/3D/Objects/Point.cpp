// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Point.hpp>

#include <OpenSpaceToolkit/Core/Types/Shared.hpp>


using ostk::core::ctnr::Array ;

void                            set_point_3_array                           (   const   Array<ostk::math::geom::d3::objects::Point>& anArray                    )
{
    (void) anArray ;
}

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Point (        pybind11::module&  aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Shared ;
    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;

    class_<Point, Object>(aModule, "Point")

        .def
        (
            init<const Real&, const Real&, const Real&>(),
            arg("first_coordinate"),
            arg("second_coordinate"),
            arg("third_coordinate")
        )

        .def(self == self)
        .def(self != self)

        .def(self + Vector3d())
        .def(self - Vector3d())

        .def(self - self)

        .def("__str__", &(shiftToString<Point>))
        .def("__repr__", &(shiftToString<Point>))

        .def("is_defined", &Point::isDefined)
        .def("is_near", &Point::isNear, arg("point"), arg("tolerance"))

        .def("x", &Point::x, return_value_policy::reference)
        .def("y", &Point::y, return_value_policy::reference)
        .def("z", &Point::z, return_value_policy::reference)
        .def("as_vector", &Point::asVector)
        .def("distance_to", &Point::distanceTo, arg("point"))
        .def("to_string", &Point::toString, arg("precision") = DEFAULT_PRECISION)
        .def("apply_transformation", &Point::applyTransformation, arg("transformation"))

        .def_static("undefined", &Point::Undefined)
        .def_static("origin", &Point::Origin)
        .def_static("vector", &Point::Vector)

    ;

    aModule.def("set_point_3_array", overload_cast<const Array<Point>&>(&set_point_3_array)) ;

}

