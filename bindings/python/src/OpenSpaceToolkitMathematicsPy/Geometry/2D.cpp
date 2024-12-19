/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Intersection.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Object.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Transformation.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D(pybind11::module& aModule)
{
    // Create "d2" python submodule
    auto d2 = aModule.def_submodule("d2");

    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::Transformation;

    class_<Object> ob(aModule, "Object");
    class_<Transformation> transf(aModule, "Transformation");

    // Add object to python "d2" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Object(d2, ob);
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Transformation(d2, transf);
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Intersection(d2);
}
