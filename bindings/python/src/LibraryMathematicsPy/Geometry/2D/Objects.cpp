////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Mathematics
/// @file           LibraryMathematicsPy/Geometry/2D/Objects.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryMathematicsPy/Geometry/2D/Objects/Polygon.cpp>
// #include <LibraryMathematicsPy/Geometry/2D/Objects/Segment.cpp>
// #include <LibraryMathematicsPy/Geometry/2D/Objects/Ray.cpp>
// #include <LibraryMathematicsPy/Geometry/2D/Objects/MultiLineString.cpp>
#include <LibraryMathematicsPy/Geometry/2D/Objects/LineString.cpp>
#include <LibraryMathematicsPy/Geometry/2D/Objects/Segment.cpp>
// #include <LibraryMathematicsPy/Geometry/2D/Objects/Ray.cpp>
// #include <LibraryMathematicsPy/Geometry/2D/Objects/Line.cpp>
#include <LibraryMathematicsPy/Geometry/2D/Objects/PointSet.cpp>
#include <LibraryMathematicsPy/Geometry/2D/Objects/Point.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_2D_Objects    ( )
{

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("Library.Mathematics.Geometry.2D.Objects")))) ;

    boost::python::scope().attr("Objects") = module ;

    boost::python::scope scope = module ;

    LibraryMathematicsPy_Geometry_2D_Objects_Point() ;
    LibraryMathematicsPy_Geometry_2D_Objects_PointSet() ;
    // LibraryMathematicsPy_Geometry_2D_Objects_Line() ;
    // LibraryMathematicsPy_Geometry_2D_Objects_Ray() ;
    LibraryMathematicsPy_Geometry_2D_Objects_Segment() ;
    LibraryMathematicsPy_Geometry_2D_Objects_LineString() ;
    // LibraryMathematicsPy_Geometry_2D_Objects_MultiLineString() ;
    LibraryMathematicsPy_Geometry_2D_Objects_Polygon() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
