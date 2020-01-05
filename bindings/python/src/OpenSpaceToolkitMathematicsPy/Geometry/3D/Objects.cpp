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

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects    ( )
{

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("ostk.mathematics.geometry.d3.objects")))) ;

    boost::python::scope().attr("objects") = module ;

    boost::python::scope scope = module ;

    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Point() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_PointSet() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Line() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Ray() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Segment() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_LineString() ;
    // OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_MultiLineString() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Plane() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Polygon() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Cuboid() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Sphere() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Ellipsoid() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Pyramid() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Cone() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Composite() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
