/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Intersection.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Object.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Transformation.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D(pybind11::module& aModule)
{
    using ostk::math::geometry::d2::Intersection;
    using ostk::math::geometry::d2::Object;
    using ostk::math::geometry::d2::Transformation;
    // Create "d2" python submodule
    auto d2 = aModule.def_submodule("d2");

    pybind11::class_<Object> objectClass(d2, "Object");
    pybind11::class_<Transformation> transformationClass(d2, "Transformation");
    pybind11::class_<Intersection> intersectionClass(d2, "Intersection");

    // Add object to python "d2" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Object(objectClass);
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Transformation(transformationClass);
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Intersection(intersectionClass);
}
