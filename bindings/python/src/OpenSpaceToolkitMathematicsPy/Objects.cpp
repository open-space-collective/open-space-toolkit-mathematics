/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Objects/Interval.cpp>

// #include <OpenSpaceToolkitMathematicsPy/Objects/Vector.cpp>

inline void OpenSpaceToolkitMathematicsPy_Objects(pybind11::module& aModule)
{
    // Create "objects" python submodule
    auto objects = aModule.def_submodule("objects");

    // Add __path__ attribute for "objects" submodule
    objects.attr("__path__") = "ostk.mathematics.objects";

    // Add objects to python "objects" submodules
    OpenSpaceToolkitMathematicsPy_Objects_Interval(objects);
    // OpenSpaceToolkitMathematicsPy_Objects_Vector(objects) ;
}
