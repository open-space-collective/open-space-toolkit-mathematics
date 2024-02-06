/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Cuboid.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Cuboid(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;

    using ostk::math::object::Vector3d;
    using ostk::math::geometry::d3::Object;
    using ostk::math::geometry::d3::objects::Point;
    using ostk::math::geometry::d3::objects::PointSet;
    using ostk::math::geometry::d3::objects::Line;
    using ostk::math::geometry::d3::objects::Ray;
    using ostk::math::geometry::d3::objects::Segment;
    using ostk::math::geometry::d3::objects::Plane;
    using ostk::math::geometry::d3::objects::Sphere;
    using ostk::math::geometry::d3::objects::Cuboid;
    using ostk::math::geometry::d3::objects::Pyramid;
    using ostk::math::geometry::d3::Intersection;
    using ostk::math::geometry::d3::transformation::rotation::Quaternion;

    //     scope in_Cuboid = class_<Cuboid, Shared<Cuboid>, bases<Object>>("Cuboid", no_init)
    class_<Cuboid, Object>(aModule, "Cuboid")

        .def(
            "__init__",
            [](Cuboid& aCuboid, const Point& aCenter, const pybind11::list& anAxisList, const pybind11::list& anExtent)
            {
                const std::array<Vector3d, 3> axes = {
                    pybind11::cast<Vector3d>(anAxisList[0]),
                    pybind11::cast<Vector3d>(anAxisList[1]),
                    pybind11::cast<Vector3d>(anAxisList[2])};
                const std::array<Real, 3> extent = {
                    pybind11::cast<Real>(anExtent[0]),
                    pybind11::cast<Real>(anExtent[1]),
                    pybind11::cast<Real>(anExtent[2])};

                new (&aCuboid) Cuboid(aCenter, axes, extent);
                // Default policy is unique pointer
                // return std::make_shared<Cuboid>(aCenter, axes, extent) ;
                // return std::shared_ptr<Cuboid>(new Cuboid(aCenter, axes, extent)) ;  // Check if that one provides
                // the correct behavior
            },
            arg("center"),
            arg("axes"),
            arg("extent")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Cuboid>))
        .def("__repr__", &(shiftToString<Cuboid>))

        .def("is_defined", &Cuboid::isDefined)
        .def("is_near", &Cuboid::isNear)

        .def("intersects", overload_cast<const Point&>(&Cuboid::intersects, const_), arg("point"))
        .def("intersects", overload_cast<const PointSet&>(&Cuboid::intersects, const_), arg("point_set"))
        .def("intersects", overload_cast<const Line&>(&Cuboid::intersects, const_), arg("line"))
        .def("intersects", overload_cast<const Cuboid&>(&Cuboid::intersects, const_), arg("cuboid"))

        .def("get_center", &Cuboid::getCenter)
        .def("get_first_axis", &Cuboid::getFirstAxis)
        .def("get_second_axis", &Cuboid::getSecondAxis)
        .def("get_third_axis", &Cuboid::getThirdAxis)
        .def("get_first_extent", &Cuboid::getFirstExtent)
        .def("get_second_extent", &Cuboid::getSecondExtent)
        .def("get_third_extent", &Cuboid::getThirdExtent)
        .def("get_vertices", &Cuboid::getVertices)
        .def("apply_transformation", &Cuboid::applyTransformation, arg("transformation"))

        .def_static("undefined", &Cuboid::Undefined)
        .def_static("cube", &Cuboid::Cube, arg("center"), arg("extent"))

        ;
}
