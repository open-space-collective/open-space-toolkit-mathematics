////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Transformations/Rotations.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryMathematicsPy/Geometry/3D/Transformations/Rotations/Quaternion.cpp>
#include <LibraryMathematicsPy/Geometry/3D/Transformations/Rotations/RotationVector.cpp>
#include <LibraryMathematicsPy/Geometry/3D/Transformations/Rotations/RotationMatrix.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Transformations_Rotations ( )
{
    
    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("Library.Mathematics.Geometry.D3.Transformations.Rotations")))) ;
    
    boost::python::scope().attr("Rotations") = module ;
    
    boost::python::scope scope = module ;
    
    LibraryMathematicsPy_Geometry_3D_Transformations_Rotations_Quaternion() ;
    LibraryMathematicsPy_Geometry_3D_Transformations_Rotations_RotationVector() ;
    LibraryMathematicsPy_Geometry_3D_Transformations_Rotations_RotationMatrix() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////