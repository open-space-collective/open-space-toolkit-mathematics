/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/PointSet.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Intersection, MoveConstructor)
{
    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;

    {
        Intersection intersection = Intersection::PointSet(PointSet({Point(1.0, 2.0, 3.0), Point(4.0, 5.0, 6.0)}));

        const Object* pointSetPtr = &intersection.accessComposite().accessObjectAt(0);

        const Intersection movedIntersection(std::move(intersection));

        EXPECT_EQ(Intersection::Type::PointSet, movedIntersection.getType());
        EXPECT_EQ(PointSet({Point(1.0, 2.0, 3.0), Point(4.0, 5.0, 6.0)}), movedIntersection.as<PointSet>());

        // The objects are moved, not cloned

        EXPECT_EQ(pointSetPtr, &movedIntersection.accessComposite().accessObjectAt(0));
    }

    {
        Intersection intersection = Intersection::Empty();

        const Intersection movedIntersection(std::move(intersection));

        EXPECT_TRUE(movedIntersection.isEmpty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Intersection, MoveAssignmentOperator)
{
    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;

    {
        Intersection intersection = Intersection::Point(Point(1.0, 2.0, 3.0));

        const Object* pointPtr = &intersection.accessComposite().accessObjectAt(0);

        Intersection otherIntersection = Intersection::Undefined();

        otherIntersection = std::move(intersection);

        EXPECT_EQ(Intersection::Type::Point, otherIntersection.getType());
        EXPECT_EQ(Point(1.0, 2.0, 3.0), otherIntersection.as<Point>());
        EXPECT_EQ(pointPtr, &otherIntersection.accessComposite().accessObjectAt(0));
    }

    {
        Intersection intersection = Intersection::Undefined();

        Intersection otherIntersection = Intersection::Point(Point(1.0, 2.0, 3.0));

        otherIntersection = std::move(intersection);

        EXPECT_FALSE(otherIntersection.isDefined());
    }
}
