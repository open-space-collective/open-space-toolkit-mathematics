////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Composite.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Cone.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Pyramid.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Ellipsoid.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Sphere.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Cuboid.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Polygon.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Plane.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Segment.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Ray.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/LineString.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Line.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/PointSet.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Point.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects                    (    pybind11::module&                     aModule        )
{

    // Create "objects" python submodule
    auto objects = aModule.def_submodule("objects") ;

    // Add __path__ attribute for "objects" submodule
    objects.attr("__path__") = "ostk.mathematics.geometry.d3.objects" ;

    // Add objects to python "objects" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Point(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_PointSet(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Line(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Ray(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Segment(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_LineString(objects) ;
    // OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_MultiLineString(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Plane(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Polygon(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Cuboid(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Sphere(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Ellipsoid(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Pyramid(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Cone(objects) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Composite(objects) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
