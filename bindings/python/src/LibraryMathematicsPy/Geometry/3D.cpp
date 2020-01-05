////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryMathematicsPy/Geometry/3D/Intersection.cpp>
#include <LibraryMathematicsPy/Geometry/3D/Transformations.cpp>
#include <LibraryMathematicsPy/Geometry/3D/Transformation.cpp>
#include <LibraryMathematicsPy/Geometry/3D/Objects.cpp>
#include <LibraryMathematicsPy/Geometry/3D/Object.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D            ( )
{

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("Library.Mathematics.Geometry.D3")))) ;

    boost::python::scope().attr("D3") = module ;

    boost::python::scope scope = module ;

    LibraryMathematicsPy_Geometry_3D_Object() ;
    LibraryMathematicsPy_Geometry_3D_Objects() ;
    LibraryMathematicsPy_Geometry_3D_Transformation() ;
    LibraryMathematicsPy_Geometry_3D_Transformations() ;
    LibraryMathematicsPy_Geometry_3D_Intersection() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
