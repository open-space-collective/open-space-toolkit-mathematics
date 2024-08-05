/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Plane.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Plane(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::object::Vector3d;

    class_<Plane, Object>(aModule, "Plane")

        .def(init<const Point&, const Vector3d&>(), arg("point"), arg("normal_vector"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Plane>))
        .def("__repr__", &(shiftToString<Plane>))

        .def("is_defined", &Plane::isDefined)

        .def("intersects", overload_cast<const Point&>(&Plane::intersects, const_), arg("point"))
        .def("intersects", overload_cast<const PointSet&>(&Plane::intersects, const_), arg("point_set"))
        .def("intersects", overload_cast<const Line&>(&Plane::intersects, const_), arg("line"))
        .def("intersects", overload_cast<const Ray&>(&Plane::intersects, const_), arg("ray"))
        .def("intersects", overload_cast<const Segment&>(&Plane::intersects, const_), arg("segment"))
        .def("contains", overload_cast<const Point&>(&Plane::contains, const_), arg("point"))
        .def("contains", overload_cast<const PointSet&>(&Plane::contains, const_), arg("point_set"))
        .def("contains", overload_cast<const Line&>(&Plane::contains, const_), arg("line"))
        .def("contains", overload_cast<const Ray&>(&Plane::contains, const_), arg("ray"))
        .def("contains", overload_cast<const Segment&>(&Plane::contains, const_), arg("segment"))

        .def("get_point", &Plane::getPoint)
        .def("get_normal_vector", &Plane::getNormalVector)
        .def("intersection_with", overload_cast<const Point&>(&Plane::intersectionWith, const_), arg("point"))
        .def("intersection_with", overload_cast<const PointSet&>(&Plane::intersectionWith, const_), arg("point_set"))
        .def("intersection_with", overload_cast<const Line&>(&Plane::intersectionWith, const_), arg("line"))
        .def("intersection_with", overload_cast<const Ray&>(&Plane::intersectionWith, const_), arg("ray"))
        .def("intersection_with", overload_cast<const Segment&>(&Plane::intersectionWith, const_), arg("segment"))
        .def("apply_transformation", &Plane::applyTransformation, arg("transformation"))

        .def_static("undefined", &Plane::Undefined)

        ;
}
