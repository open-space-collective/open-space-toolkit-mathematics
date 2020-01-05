////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Cone.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Cone.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, Constructor)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Cone ;

    {

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        EXPECT_NO_THROW(Cone(apex, axis, angle)) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, Clone)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Cone ;

    {

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        EXPECT_NO_THROW(const Cone* conePtr = Cone(apex, axis, angle).clone() ; delete conePtr ;) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, EqualToOperator)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Cone ;

    {

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        EXPECT_TRUE(Cone(apex, axis, angle) == Cone(apex, axis, angle)) ;

    }

    {

        const Point firstApex = { 0.0, 0.0, 0.0 } ;
        const Vector3d firstAxis = { +1.0, 0.0, 0.0 } ;
        const Angle firstAngle = Angle::Degrees(135.0) ;

        const Cone firstCone = { firstApex, firstAxis, firstAngle } ;

        const Point secondApex = { 0.0, 0.0, 0.0 } ;
        const Vector3d secondXis = { -1.0, 0.0, 0.0 } ;
        const Angle secondAngle = Angle::Degrees(45.0) ;

        const Cone secondCone = { secondApex, secondXis, secondAngle } ;

        EXPECT_TRUE(firstCone == secondCone) ;

    }

    {

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        EXPECT_FALSE(Cone(apex, axis, angle) == Cone::Undefined()) ;
        EXPECT_FALSE(Cone::Undefined() == Cone(apex, axis, angle)) ;
        EXPECT_FALSE(Cone::Undefined() == Cone::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, NotEqualToOperator)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Cone ;

    {

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        EXPECT_FALSE(Cone(apex, axis, angle) != Cone(apex, axis, angle)) ;

    }

    {

        const Point firstApex = { 0.0, 0.0, 0.0 } ;
        const Vector3d firstAxis = { +1.0, 0.0, 0.0 } ;
        const Angle firstAngle = Angle::Degrees(135.0) ;

        const Cone firstCone = { firstApex, firstAxis, firstAngle } ;

        const Point secondApex = { 0.0, 0.0, 0.0 } ;
        const Vector3d secondXis = { -1.0, 0.0, 0.0 } ;
        const Angle secondAngle = Angle::Degrees(45.0) ;

        const Cone secondCone = { secondApex, secondXis, secondAngle } ;

        EXPECT_FALSE(firstCone != secondCone) ;

    }

    {

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        EXPECT_TRUE(Cone(apex, axis, angle) != Cone::Undefined()) ;
        EXPECT_TRUE(Cone::Undefined() != Cone(apex, axis, angle)) ;
        EXPECT_TRUE(Cone::Undefined() != Cone::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, StreamOperator)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Cone ;

    {

        testing::internal::CaptureStdout() ;

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        EXPECT_NO_THROW(std::cout << Cone(apex, axis, angle) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, IsDefined)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Cone ;

    {

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        EXPECT_TRUE(Cone(apex, axis, angle).isDefined()) ;

    }

    {

        EXPECT_FALSE(Cone::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, Intersects_Ellipsoid)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Cone ;

    {

        const Point apex = { -10.0, 0.0, 10.0 } ;
        const Vector3d axis = Vector3d::X() ;
        const Angle angle = Angle::Degrees(10.0) ;

        const Cone cone = { apex, axis, angle } ;

        const Ellipsoid ellipsoid = { { 0.0, 0.0, 10.0 }, 5.0, 5.0, 5.0 } ;

        EXPECT_TRUE(cone.intersects(ellipsoid)) ;

    }

    {

        EXPECT_ANY_THROW(Cone::Undefined().intersects(Ellipsoid::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, GetApex)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Cone ;

    {

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        EXPECT_EQ(apex, Cone(apex, axis, angle).getApex()) ;

    }

    {

        EXPECT_ANY_THROW(Cone::Undefined().getApex()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, GetAxis)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Cone ;

    {

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        EXPECT_EQ(axis, Cone(apex, axis, angle).getAxis()) ;

    }

    {

        EXPECT_ANY_THROW(Cone::Undefined().getAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, GetAngle)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Cone ;

    {

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        EXPECT_EQ(angle, Cone(apex, axis, angle).getAngle()) ;

    }

    {

        EXPECT_ANY_THROW(Cone::Undefined().getAngle()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, GetRaysOfLateralSurface)
{

    using library::core::types::Real ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Cone ;

    {

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        const Array<Ray> rays = Cone(apex, axis, angle).getRaysOfLateralSurface(4) ;

        const Array<Ray> referenceRays =
        {
            { apex, { 0.707106781186548, 0.0, 0.707106781186547 } },
            { apex, { 1.11022302462516e-16, 0.707106781186548, 0.707106781186547 } },
            { apex, { -0.707106781186548, 8.65956056235493e-17, 0.707106781186547 } },
            { apex, { -1.11022302462516e-16, -0.707106781186548, 0.707106781186547 } }
        } ;

        EXPECT_TRUE
        (
            rays.isNear
            (
                referenceRays,
                [] (const Ray& aFirstRay, const Ray& aSecondRay) -> bool
                {

                    return aFirstRay.getOrigin().isNear(aSecondRay.getOrigin(), Real::Epsilon())
                        && aFirstRay.getDirection().isNear(aSecondRay.getDirection(), Real::Epsilon()) ;

                }
            )
        ) ;

    }

    {

        EXPECT_ANY_THROW(Cone::Undefined().getRaysOfLateralSurface()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, IntersectionWith_Ellipsoid)
{

    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::LineString ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Cone ;
    using library::math::geom::d3::Intersection ;

    {

        const Point apex = { 10.0, 0.0, 10.0 } ;
        const Vector3d axis = { -1.0, 0.0, 0.0 } ;
        const Angle angle = Angle::Degrees(10.0) ;

        const Cone cone = { apex, axis, angle } ;

        const Ellipsoid ellipsoid = { { 0.0, 0.0, 10.0 }, 5.0, 5.0, 5.0 } ;

        const Intersection intersection = cone.intersectionWith(ellipsoid, true, 4) ;

        EXPECT_TRUE(intersection.isDefined()) ;
        EXPECT_FALSE(intersection.isEmpty()) ;
        EXPECT_TRUE(intersection.accessComposite().is<LineString>()) ;

        const LineString intersectionLineString = intersection.accessComposite().as<LineString>() ;

        EXPECT_EQ(4, intersectionLineString.getPointCount()) ;

        const LineString referenceLineString =
        {
            {
                { 4.91908097261278, 0.895903111323379, 10.0 },
                { 4.91908097261278, 0.0, 9.10409688867662 },
                { 4.91908097261278, -0.895903111323379, 10.0 },
                { 4.91908097261278, 0.0, 10.8959031113234 },
            }
        } ;

        EXPECT_TRUE(intersectionLineString.isNear(referenceLineString, 1e-10)) ;

    }

    {

        EXPECT_ANY_THROW(Cone::Undefined().intersectionWith(Ellipsoid::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, ApplyTransformation)
{

    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Cone ;
    using library::math::geom::d3::Transformation ;
    using library::math::geom::d3::trf::rot::RotationVector ;

    // Translation

    {

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        Cone cone = { apex, axis, angle } ;

        cone.applyTransformation(Transformation::Translation({ 4.0, 5.0, 6.0 })) ;

        EXPECT_EQ(Cone({ 4.0, 5.0, 6.0 }, axis, angle), cone) ;

    }

    // Rotation

    {

        const Point apex = { 0.0, 1.0, 0.0 } ;
        const Vector3d axis = { 0.0, 1.0, 0.0 } ;
        const Angle angle = Angle::Degrees(45.0) ;

        Cone cone = { apex, axis, angle } ;

        cone.applyTransformation(Transformation::Rotation(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(90.0)))) ;

        const Point referenceApex = { 0.0, 0.0, 1.0 } ;
        const Vector3d referenceAxis = { 0.0, 0.0, 1.0 } ;
        const Angle referenceAngle = Angle::Degrees(45.0) ;

        const Cone referenceCone = { referenceApex, referenceAxis, referenceAngle } ;

        EXPECT_TRUE(cone.getApex().isNear(referenceCone.getApex(), Real::Epsilon())) << referenceCone.getApex().toString() << cone.getApex().toString() ;
        EXPECT_TRUE(cone.getAxis().isNear(referenceCone.getAxis(), Real::Epsilon())) << referenceCone.getAxis().toString() << cone.getAxis().toString() ;
        EXPECT_TRUE(cone.getAngle().inDegrees().isNear(referenceCone.getAngle().inDegrees(), Real::Epsilon())) << referenceCone.getAngle().toString() << cone.getAngle().toString() ;

    }

    {

        const Point apex = { 0.0, 0.0, 0.0 } ;
        const Vector3d axis = Vector3d::Z() ;
        const Angle angle = Angle::Degrees(45.0) ;

        EXPECT_ANY_THROW(Cone::Undefined().applyTransformation(Transformation::Undefined())) ;
        EXPECT_ANY_THROW(Cone::Undefined().applyTransformation(Transformation::Identity())) ;
        EXPECT_ANY_THROW(Cone(apex, axis, angle).applyTransformation(Transformation::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, Undefined)
{

    using library::math::geom::d3::objects::Cone ;

    {

        EXPECT_NO_THROW(Cone::Undefined()) ;
        EXPECT_FALSE(Cone::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
