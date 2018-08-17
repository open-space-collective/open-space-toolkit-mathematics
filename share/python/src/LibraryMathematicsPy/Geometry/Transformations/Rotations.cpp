////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/Transformations/Rotations.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryMathematicsPy/Geometry/Transformations/Rotations/Quaternion.cpp>
#include <LibraryMathematicsPy/Geometry/Transformations/Rotations/RotationVector.cpp>
#include <LibraryMathematicsPy/Geometry/Transformations/Rotations/RotationMatrix.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_Transformations_Rotations ( )
{
    
    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("Library.Mathematics.Geometry.Transformations.Rotations")))) ;
    
    boost::python::scope().attr("Rotations") = module ;
    
    boost::python::scope scope = module ;
    
    LibraryMathematicsPy_Geometry_Transformations_Rotations_Quaternion() ;
    LibraryMathematicsPy_Geometry_Transformations_Rotations_RotationVector() ;
    LibraryMathematicsPy_Geometry_Transformations_Rotations_RotationMatrix() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////