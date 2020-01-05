////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/PointSet.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/PointSet.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, Constructor)
{

    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::PointSet ;

    {

        EXPECT_NO_THROW(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } })) ;

    }

    {

        EXPECT_NO_THROW(PointSet({ { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } })) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, Clone)
{

    using ostk::math::geom::d2::objects::PointSet ;

    {

        EXPECT_NO_THROW(const PointSet* pointSetPtr = PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).clone() ; delete pointSetPtr ;) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, EqualToOperator)
{

    using ostk::math::geom::d2::objects::PointSet ;

    {

        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) == PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } })) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) == PointSet({ { 0.0, 0.0 }, { 0.0, 2.0 }, { 0.0, 1.0 } })) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) == PointSet({ { 0.0, 1.0 }, { 0.0, 0.0 }, { 0.0, 2.0 } })) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) == PointSet({ { 0.0, 1.0 }, { 0.0, 2.0 }, { 0.0, 0.0 } })) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) == PointSet({ { 0.0, 2.0 }, { 0.0, 0.0 }, { 0.0, 1.0 } })) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) == PointSet({ { 0.0, 2.0 }, { 0.0, 1.0 }, { 0.0, 0.0 } })) ;

        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) == PointSet({ { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } })) ;

        EXPECT_TRUE(PointSet::Empty() == PointSet::Empty()) ;

    }

    {

        EXPECT_FALSE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) == PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 3.0 } })) ;

    }

    {

        EXPECT_FALSE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) == PointSet::Empty()) ;
        EXPECT_FALSE(PointSet::Empty() == PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } })) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, NotEqualToOperator)
{

    using ostk::math::geom::d2::objects::PointSet ;

    {

        EXPECT_FALSE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) != PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } })) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) != PointSet({ { 0.0, 0.0 }, { 0.0, 2.0 }, { 0.0, 1.0 } })) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) != PointSet({ { 0.0, 1.0 }, { 0.0, 0.0 }, { 0.0, 2.0 } })) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) != PointSet({ { 0.0, 1.0 }, { 0.0, 2.0 }, { 0.0, 0.0 } })) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) != PointSet({ { 0.0, 2.0 }, { 0.0, 0.0 }, { 0.0, 1.0 } })) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) != PointSet({ { 0.0, 2.0 }, { 0.0, 1.0 }, { 0.0, 0.0 } })) ;

        EXPECT_FALSE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) != PointSet({ { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } })) ;

        EXPECT_FALSE(PointSet::Empty() != PointSet::Empty()) ;

    }

    {

        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) != PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 3.0 } })) ;

    }

    {

        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) != PointSet::Empty()) ;
        EXPECT_TRUE(PointSet::Empty() != PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } })) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, StreamOperator)
{

    using ostk::math::geom::d2::objects::PointSet ;

    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, IsDefined)
{

    using ostk::math::geom::d2::objects::PointSet ;

    {

        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).isDefined()) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } }).isDefined()) ;

    }

    {

        EXPECT_FALSE(PointSet::Empty().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, IsEmpty)
{

    using ostk::math::geom::d2::objects::PointSet ;

    {

        EXPECT_FALSE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).isEmpty()) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } }).isEmpty()) ;

    }

    {

        EXPECT_TRUE(PointSet::Empty().isEmpty()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, IsNear)
{

    using ostk::core::types::Real ;

    using ostk::math::geom::d2::objects::PointSet ;

    {

        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).isNear(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }), Real::Epsilon())) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).isNear(PointSet({ { 0.0, 1.0 }, { 0.0, 0.0 }, { 0.0, 2.0 } }), Real::Epsilon())) ;

        EXPECT_TRUE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).isNear(PointSet({ { 0.0, Real::Epsilon() }, { Real::Epsilon(), 1.0 }, { 0.0, 2.0 } }), Real::Epsilon())) ;

    }

    {

        EXPECT_FALSE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).isNear(PointSet({ { 0.0, 2.0 * Real::Epsilon() }, { Real::Epsilon(), 1.0 }, { 0.0, 2.0 } }), Real::Epsilon())) ;

    }

    {

        EXPECT_FALSE(PointSet::Empty().isNear(PointSet::Empty(), Real::Epsilon())) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).isNear(PointSet::Empty(), Real::Epsilon())) ;
        EXPECT_FALSE(PointSet::Empty().isNear(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }), Real::Epsilon())) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, GetSize)
{

    using ostk::math::geom::d2::objects::PointSet ;

    {

        EXPECT_EQ(3, PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).getSize()) ;

    }

    {

        EXPECT_EQ(0, PointSet::Empty().getSize()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, GetPointClosestTo)
{

    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::PointSet ;

    {

        EXPECT_EQ(Point(0.0, 0.0), PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).getPointClosestTo({ 0.0, 0.0 })) ;
        EXPECT_EQ(Point(0.0, 1.0), PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).getPointClosestTo({ 0.0, 1.0 })) ;
        EXPECT_EQ(Point(0.0, 2.0), PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).getPointClosestTo({ 0.0, 2.0 })) ;

    }

    {

        EXPECT_ANY_THROW(PointSet::Empty().getPointClosestTo(Point::Undefined())) ;
        EXPECT_ANY_THROW(PointSet::Empty().getPointClosestTo(Point::Origin())) ;
        EXPECT_ANY_THROW(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).getPointClosestTo(Point::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, ToString)
{

    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::PointSet ;

    {

        EXPECT_EQ("[[0.0, 2.0], [0.0, 1.0], [0.0, 0.0]]", PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).toString()) ;
        EXPECT_EQ("[[0.0, 2.0], [0.0, 1.0], [0.0, 0.0]]", PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).toString(Point::Format::Standard)) ;

    }

    {

        EXPECT_EQ("[[0.0000000000, 2.0000000000], [0.0000000000, 1.0000000000], [0.0000000000, 0.0000000000]]", PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).toString(Point::Format::Standard, 10)) ;

    }

    {

        EXPECT_EQ("[]", PointSet::Empty().toString()) ;

    }

    {

        EXPECT_ANY_THROW(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).toString(Point::Format::WKT)) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, ConstIterator)
{

    using ostk::core::types::Index ;

    using ostk::math::geom::d2::objects::PointSet ;

    {

        const PointSet pointSet = { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } } } ;

        Index count = 0 ;

        for (const auto& point : pointSet)
        {

            EXPECT_TRUE(point.isDefined()) ;

            count++ ;

        }

        EXPECT_EQ(3, count) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, ApplyTransformation)
{

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::PointSet ;
    using ostk::math::geom::d2::Transformation ;

    // Translation

    {

        PointSet pointSet = { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } } } ;

        pointSet.applyTransformation(Transformation::Translation({ 4.0, 5.0 })) ;

        EXPECT_EQ(PointSet({ { 4.0, 5.0 }, { 4.0, 6.0 }, { 4.0, 7.0 } }), pointSet) ;

    }

    {

        EXPECT_ANY_THROW(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 0.0, 2.0 } }).applyTransformation(Transformation::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_PointSet, Empty)
{

    using ostk::math::geom::d2::objects::PointSet ;

    {

        EXPECT_NO_THROW(PointSet::Empty()) ;
        EXPECT_FALSE(PointSet::Empty().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
