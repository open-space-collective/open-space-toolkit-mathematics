////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryMathematicsPy/Geometry/3D/Objects/Ellipsoid.cpp>
#include <LibraryMathematicsPy/Geometry/3D/Objects/Sphere.cpp>
#include <LibraryMathematicsPy/Geometry/3D/Objects/Segment.cpp>
#include <LibraryMathematicsPy/Geometry/3D/Objects/Point.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects    ( )
{
    
    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("Library.Mathematics.Geometry.3D.Objects")))) ;
    
    boost::python::scope().attr("Objects") = module ;
    
    boost::python::scope scope = module ;
    
    LibraryMathematicsPy_Geometry_3D_Objects_Point() ;
    LibraryMathematicsPy_Geometry_3D_Objects_Segment() ;
    LibraryMathematicsPy_Geometry_3D_Objects_Sphere() ;
    LibraryMathematicsPy_Geometry_3D_Objects_Ellipsoid() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////