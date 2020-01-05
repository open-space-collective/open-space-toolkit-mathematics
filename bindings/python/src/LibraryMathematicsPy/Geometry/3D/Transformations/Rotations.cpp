////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations/Quaternion.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations/RotationVector.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations/RotationMatrix.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations ( )
{

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("Library.Mathematics.Geometry.D3.Transformations.Rotations")))) ;

    boost::python::scope().attr("Rotations") = module ;

    boost::python::scope scope = module ;

    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_Quaternion() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_RotationVector() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_RotationMatrix() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
