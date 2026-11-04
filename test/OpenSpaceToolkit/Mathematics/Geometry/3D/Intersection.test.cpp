/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Composite.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Intersection, Constructor)
{
    using ostk::core::container::Array;
    using ostk::core::type::Unique;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Composite;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        const Intersection intersection = {Array<Unique<Object>>::Empty()};

        EXPECT_TRUE(intersection.isEmpty());
        EXPECT_EQ(Intersection::Type::Empty, intersection.getType());
    }

    {
        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty();
        objects.emplace_back(std::make_unique<Point>(0.0, 0.0, 0.0));
        objects.emplace_back(std::make_unique<Point>(1.0, 0.0, 0.0));

        const Intersection intersection = {std::move(objects)};

        EXPECT_EQ(Intersection::Type::Point, intersection.getType());
        EXPECT_FALSE(intersection.isComplex());
    }

    {
        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty();
        objects.emplace_back(std::make_unique<Point>(0.0, 0.0, 0.0));
        objects.emplace_back(std::make_unique<Segment>(Point(0.0, 0.0, 0.0), Point(1.0, 0.0, 0.0)));

        const Intersection intersection = {std::move(objects)};

        EXPECT_EQ(Intersection::Type::Complex, intersection.getType());
        EXPECT_TRUE(intersection.isComplex());
    }

    // An object without an intersection type is ignored when it comes first, and makes the intersection complex
    // otherwise (same behaviour as before Intersection::Type::Undefined was removed)

    {
        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty();
        objects.emplace_back(std::make_unique<Composite>(Composite::Empty()));
        objects.emplace_back(std::make_unique<Point>(0.0, 0.0, 0.0));

        const Intersection intersection = {std::move(objects)};

        EXPECT_EQ(Intersection::Type::Point, intersection.getType());
    }

    {
        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty();
        objects.emplace_back(std::make_unique<Point>(0.0, 0.0, 0.0));
        objects.emplace_back(std::make_unique<Composite>(Composite::Empty()));

        const Intersection intersection = {std::move(objects)};

        EXPECT_EQ(Intersection::Type::Complex, intersection.getType());
    }

    // Only objects without an intersection type: this used to build an undefined intersection, it now throws

    {
        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty();
        objects.emplace_back(std::make_unique<Composite>(Composite::Empty()));

        EXPECT_ANY_THROW(Intersection intersection(std::move(objects)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Intersection, EqualToOperator)
{
    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_TRUE(Intersection::Empty() == Intersection::Empty());
        EXPECT_TRUE(Intersection::Point(Point(0.0, 0.0, 0.0)) == Intersection::Point(Point(0.0, 0.0, 0.0)));
        EXPECT_FALSE(Intersection::Point(Point(0.0, 0.0, 0.0)) == Intersection::Point(Point(1.0, 0.0, 0.0)));
        EXPECT_FALSE(Intersection::Point(Point(0.0, 0.0, 0.0)) == Intersection::Empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Intersection, AdditionOperator)
{
    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_EQ(Intersection::Type::Empty, (Intersection::Empty() + Intersection::Empty()).getType());
        EXPECT_EQ(
            Intersection::Type::Point, (Intersection::Empty() + Intersection::Point(Point(0.0, 0.0, 0.0))).getType()
        );
    }

    {
        Intersection intersection = Intersection::Point(Point(0.0, 0.0, 0.0));

        intersection += Intersection::Point(Point(1.0, 0.0, 0.0));

        EXPECT_EQ(Intersection::Type::Point, intersection.getType());
        EXPECT_EQ(2, intersection.accessComposite().getObjectCount());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Intersection, AccessComposite)
{
    using ostk::mathematics::geometry::d3::Intersection;

    {
        EXPECT_TRUE(Intersection::Empty().accessComposite().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Intersection, StringFromType)
{
    using ostk::mathematics::geometry::d3::Intersection;

    {
        EXPECT_EQ("Empty", Intersection::StringFromType(Intersection::Type::Empty));
        EXPECT_EQ("Point", Intersection::StringFromType(Intersection::Type::Point));
        EXPECT_EQ("Complex", Intersection::StringFromType(Intersection::Type::Complex));
    }
}
