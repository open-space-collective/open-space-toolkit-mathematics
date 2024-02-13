/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Object/Interval.cpp>

// #include <OpenSpaceToolkitMathematicsPy/Object/Vector.cpp>

inline void OpenSpaceToolkitMathematicsPy_Object(pybind11::module& aModule)
{
    // Create "object" python submodule
    auto object = aModule.def_submodule("object");


    // Add object to python "object" submodules
    OpenSpaceToolkitMathematicsPy_Object_Interval(object);
    // OpenSpaceToolkitMathematicsPy_Object_Vector(object) ;
}
