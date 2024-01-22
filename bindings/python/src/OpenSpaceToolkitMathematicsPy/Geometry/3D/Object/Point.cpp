/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>

using ostk::core::ctnr::Array;

void set_point_3_array(const Array<ostk::mathematics::geometry::d3::object::Point>& anArray)
{
    (void)anArray;
}

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Point(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Shared;
    using ostk::core::types::Integer;
    using ostk::core::types::Real;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;

    class_<Point, Object>(aModule, "Point")

        .def(
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

    aModule.def("set_point_3_array", overload_cast<const Array<Point>&>(&set_point_3_array));
}
