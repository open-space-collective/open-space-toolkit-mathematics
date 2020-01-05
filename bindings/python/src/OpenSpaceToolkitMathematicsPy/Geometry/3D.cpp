////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Intersection.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformation.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D   ( )
{

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("ostk.mathematics.geometry.d3")))) ;

    boost::python::scope().attr("d3") = module ;

    boost::python::scope scope = module ;

    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations() ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Intersection() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
