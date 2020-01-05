////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Polygon.cpp>
// #include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Segment.cpp>
// #include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Ray.cpp>
// #include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/MultiLineString.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/LineString.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Segment.cpp>
// #include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Ray.cpp>
// #include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Line.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/PointSet.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Point.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects    ( )
{

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("Library.Mathematics.Geometry.2D.Objects")))) ;

    boost::python::scope().attr("Objects") = module ;

    boost::python::scope scope = module ;

    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Point() ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_PointSet() ;
    // OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Line() ;
    // OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Ray() ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Segment() ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_LineString() ;
    // OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_MultiLineString() ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Polygon() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
