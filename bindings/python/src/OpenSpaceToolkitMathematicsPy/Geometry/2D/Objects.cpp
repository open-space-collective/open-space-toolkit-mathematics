////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Composite.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/MultiPolygon.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Polygon.cpp>
// #include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/MultiLineString.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/LineString.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Segment.cpp>
// #include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Ray.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Line.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/PointSet.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Point.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects (         pybind11::module&       aModule                                     )
{

    // Create "objects" python submodule
    auto objects = aModule.def_submodule("objects") ;

    // Add __path__ attribute for "objects" submodule
    objects.attr("__path__") = "ostk.mathematics.geometry.d2.objects" ;

    // Add objects to python "objects" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Point(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_PointSet(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Line(objects) ;
    // OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Ray(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Segment(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_LineString(objects) ;
    // OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_MultiLineString(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Polygon(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_MultiPolygon(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Composite(objects) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
