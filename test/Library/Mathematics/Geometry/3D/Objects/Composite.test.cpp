////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Composite.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Composite.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Cuboid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Line.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/PointSet.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>

#include <Library/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, Constructor)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        EXPECT_NO_THROW(Composite composite(pyramid) ;) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

        EXPECT_NO_THROW(Composite composite(pyramidUPtr) ;) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

        objects.emplace_back(std::move(pyramidUPtr)) ;
        objects.emplace_back(std::move(cuboidUPtr)) ;

        EXPECT_NO_THROW(Composite composite(std::move(objects)) ;) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, Clone)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        EXPECT_NO_THROW(Composite(pyramid).clone() ;) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, CopyConstructor)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_NO_THROW(Composite otherComposite(composite) ;) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, EqualToOperator)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_TRUE(composite == composite) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

        objects.emplace_back(std::move(pyramidUPtr)) ;
        objects.emplace_back(std::move(cuboidUPtr)) ;

        const Composite composite = Composite { std::move(objects) } ;

        EXPECT_TRUE(composite == composite) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite firstComposite = Composite { pyramid } ;

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        const Composite secondComposite = Composite { cuboid } ;

        EXPECT_FALSE(firstComposite == secondComposite) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

        Array<Unique<Object>> firstObjects = Array<Unique<Object>>::Empty() ;

        firstObjects.emplace_back(std::move(pyramidUPtr->clone())) ;
        firstObjects.emplace_back(std::move(cuboidUPtr->clone())) ;

        const Composite firstComposite = Composite { std::move(firstObjects) } ;

        Array<Unique<Object>> secondObjects = Array<Unique<Object>>::Empty() ;

        secondObjects.emplace_back(std::move(cuboidUPtr->clone())) ;
        secondObjects.emplace_back(std::move(pyramidUPtr->clone())) ;

        const Composite secondComposite = Composite { std::move(secondObjects) } ;

        EXPECT_FALSE(firstComposite == secondComposite) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_FALSE(Composite::Undefined() == Composite::Undefined()) ;
        EXPECT_FALSE(Composite::Undefined() == composite) ;
        EXPECT_FALSE(composite == Composite::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, NotEqualToOperator)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_FALSE(composite != composite) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

        objects.emplace_back(std::move(pyramidUPtr)) ;
        objects.emplace_back(std::move(cuboidUPtr)) ;

        const Composite composite = Composite { std::move(objects) } ;

        EXPECT_FALSE(composite != composite) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite firstComposite = Composite { pyramid } ;

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        const Composite secondComposite = Composite { cuboid } ;

        EXPECT_TRUE(firstComposite != secondComposite) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

        Array<Unique<Object>> firstObjects = Array<Unique<Object>>::Empty() ;

        firstObjects.emplace_back(std::move(pyramidUPtr->clone())) ;
        firstObjects.emplace_back(std::move(cuboidUPtr->clone())) ;

        const Composite firstComposite = Composite { std::move(firstObjects) } ;

        Array<Unique<Object>> secondObjects = Array<Unique<Object>>::Empty() ;

        secondObjects.emplace_back(std::move(cuboidUPtr->clone())) ;
        secondObjects.emplace_back(std::move(pyramidUPtr->clone())) ;

        const Composite secondComposite = Composite { std::move(secondObjects) } ;

        EXPECT_TRUE(firstComposite != secondComposite) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_TRUE(Composite::Undefined() != Composite::Undefined()) ;
        EXPECT_TRUE(Composite::Undefined() != composite) ;
        EXPECT_TRUE(composite != Composite::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, AdditionOperator)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_NO_THROW(composite + composite) ;

    }

    {

        EXPECT_ANY_THROW(Composite::Undefined() + Composite::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, AdditionAssignmentOperator)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        Composite composite = Composite { pyramid } ;

        EXPECT_NO_THROW(composite += composite) ;

    }

    {

        Composite firstComposite = Composite::Undefined() ;

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_NO_THROW(firstComposite += composite) ;

    }

    {

        Composite composite = Composite::Undefined() ;

        EXPECT_ANY_THROW(composite += Composite::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, StreamOperator)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << composite << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, IsDefined)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_TRUE(composite.isDefined()) ;

    }

    {

        EXPECT_FALSE(Composite::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, Intersects)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    // [TBI]

    // {

    //     const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
    //     const Point apex = { 0.0, 0.0, 1.0 } ;

    //     const Pyramid pyramid = { base, apex } ;

    //     const Composite composite = Composite { pyramid } ;

    //     EXPECT_TRUE(composite.intersects(composite)) ;

    // }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_ANY_THROW(Composite::Undefined().intersects(Composite::Undefined())) ;
        EXPECT_ANY_THROW(Composite::Undefined().intersects(composite)) ;
        EXPECT_ANY_THROW(composite.intersects(Composite::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, Contains)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    // [TBI]

    // {

    //     const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
    //     const Point apex = { 0.0, 0.0, 1.0 } ;

    //     const Pyramid pyramid = { base, apex } ;

    //     const Composite composite = Composite { pyramid } ;

    //     EXPECT_TRUE(composite.contains(composite)) ;

    // }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_ANY_THROW(Composite::Undefined().contains(Composite::Undefined())) ;
        EXPECT_ANY_THROW(Composite::Undefined().contains(composite)) ;
        EXPECT_ANY_THROW(composite.contains(Composite::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, Is)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_TRUE(composite.is<Pyramid>()) ;
        
        EXPECT_FALSE(composite.is<Cuboid>()) ;

    }

    {

        EXPECT_ANY_THROW(Composite::Undefined().is<Pyramid>()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, As)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_EQ(pyramid, composite.as<Pyramid>()) ;
        
        EXPECT_ANY_THROW(composite.as<Cuboid>()) ;

    }

    {

        EXPECT_ANY_THROW(Composite::Undefined().as<Pyramid>()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, AccessObjectAt)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_TRUE(composite.accessObjectAt(0).is<Pyramid>()) ;

        EXPECT_ANY_THROW(composite.accessObjectAt(1)) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

        objects.emplace_back(std::move(pyramidUPtr)) ;
        objects.emplace_back(std::move(cuboidUPtr)) ;

        const Composite composite = Composite { std::move(objects) } ;

        EXPECT_TRUE(composite.accessObjectAt(0).is<Pyramid>()) ;
        EXPECT_TRUE(composite.accessObjectAt(1).is<Cuboid>()) ;

        EXPECT_ANY_THROW(composite.accessObjectAt(2)) ;

    }

    {

        EXPECT_ANY_THROW(Composite::Undefined().accessObjectAt(0)) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, AccessObjects)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_EQ(1, composite.accessObjects().getSize()) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

        objects.emplace_back(std::move(pyramidUPtr)) ;
        objects.emplace_back(std::move(cuboidUPtr)) ;

        const Composite composite = Composite { std::move(objects) } ;

        EXPECT_EQ(2, composite.accessObjects().getSize()) ;

    }

    {

        EXPECT_ANY_THROW(Composite::Undefined().accessObjects()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, GetObjectCount)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_EQ(1, composite.getObjectCount()) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

        objects.emplace_back(std::move(pyramidUPtr)) ;
        objects.emplace_back(std::move(cuboidUPtr)) ;

        const Composite composite = Composite { std::move(objects) } ;

        EXPECT_EQ(2, composite.getObjectCount()) ;

    }

    {

        EXPECT_ANY_THROW(Composite::Undefined().getObjectCount()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, ConstIterator)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Composite composite = Composite { pyramid } ;

        EXPECT_NO_THROW
        (

            for (const auto& objectUPtr : composite)
            {
                EXPECT_TRUE(objectUPtr->isDefined()) ;
            }
            
        ) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

        objects.emplace_back(std::move(pyramidUPtr)) ;
        objects.emplace_back(std::move(cuboidUPtr)) ;

        const Composite composite = Composite { std::move(objects) } ;

        EXPECT_NO_THROW
        (

            for (const auto& objectUPtr : composite)
            {
                EXPECT_TRUE(objectUPtr->isDefined()) ;
            }
            
        ) ;

    }

    {

        EXPECT_ANY_THROW
        (
            
            for (const auto& objectUPtr : Composite::Undefined())
            {
                (void) objectUPtr ;
            }

        ) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, ApplyTransformation)
{

    using library::core::types::Unique ;
    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;
    using library::math::geom::d3::Transformation ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        Composite composite = Composite { pyramid } ;

        EXPECT_NO_THROW(composite.applyTransformation(Transformation::Identity())) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        Composite composite = Composite { pyramid } ;

        EXPECT_ANY_THROW(composite.applyTransformation(Transformation::Undefined())) ;
        EXPECT_ANY_THROW(Composite::Undefined().applyTransformation(Transformation::Undefined())) ;
        EXPECT_ANY_THROW(Composite::Undefined().applyTransformation(Transformation::Identity())) ;
        

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Composite, Undefined)
{

    using library::math::geom::d3::objects::Composite ;
    
    {

        EXPECT_NO_THROW(Composite::Undefined()) ;
        EXPECT_FALSE(Composite::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////