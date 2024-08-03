/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Composite.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, Constructor)
{
    using ostk::core::type::Unique;
    using ostk::core::container::Array;

    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        EXPECT_NO_THROW(Composite composite(polygon););
    }

    {
        const Array<Point> outerRing = {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}};
        const Array<Array<Point>> innerRings = Array<Array<Point>>::Empty();

        const Unique<Object> polygonUPtr = std::make_unique<Polygon>(outerRing, innerRings);

        EXPECT_NO_THROW(Composite composite(polygonUPtr););
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, Clone)
{
    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        EXPECT_NO_THROW(const Composite* compositePtr = Composite(polygon).clone(); delete compositePtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, CopyConstructor)
{
    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        EXPECT_NO_THROW(Composite otherComposite(composite););
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, EqualToOperator)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        EXPECT_TRUE(composite == composite);
    }

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        EXPECT_FALSE(Composite::Undefined() == Composite::Undefined());
        EXPECT_FALSE(Composite::Undefined() == composite);
        EXPECT_FALSE(composite == Composite::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, NotEqualToOperator)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        EXPECT_FALSE(composite != composite);
    }

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point point = {1.0, 2.0};

        const Composite polygonComposite = Composite {polygon};
        const Composite pointComposite = Composite {point};

        EXPECT_TRUE(polygonComposite != pointComposite);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, AdditionOperator)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        EXPECT_NO_THROW(composite + composite);
    }

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point point = {1.0, 2.0};

        const Composite polygonComposite = Composite {polygon};
        const Composite pointComposite = Composite {point};

        EXPECT_NO_THROW(polygonComposite + pointComposite);
    }

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        EXPECT_ANY_THROW(Composite::Undefined() + composite);
        EXPECT_ANY_THROW(composite + Composite::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, AdditionAssignmentOperator)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        Composite composite = Composite {polygon};

        EXPECT_NO_THROW(composite += composite);
    }

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point point = {1.0, 2.0};

        Composite composite = Composite {polygon};
        const Composite otherComposite = Composite {point};

        EXPECT_NO_THROW(composite += otherComposite);
    }

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        Composite composite = Composite {polygon};

        EXPECT_ANY_THROW(Composite::Undefined() += composite);
        EXPECT_ANY_THROW(composite += Composite::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, StreamOperator)
{
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << composite << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, IsDefined)
{
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        EXPECT_TRUE(composite.isDefined());
    }

    {
        EXPECT_FALSE(Composite::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, IsEmpty)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        EXPECT_FALSE(composite.isEmpty());
    }

    {
        EXPECT_TRUE(Composite::Empty().isEmpty());
    }

    {
        EXPECT_ANY_THROW(Composite::Undefined().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, Intersects)
{
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        // EXPECT_TRUE(composite.intersects(composite)) ; // TBI
        EXPECT_ANY_THROW(Composite::Undefined().intersects(Composite::Undefined()));
        EXPECT_ANY_THROW(Composite::Undefined().intersects(composite));
        EXPECT_ANY_THROW(composite.intersects(Composite::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, Contains)
{
    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Point point = {1.0, 0.0};

        EXPECT_FALSE(Composite::Empty().contains(point));
    }

    // Point contained in border of the Polygon as part of the Polygon definition

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        const Point point = {1.0, 0.0};

        EXPECT_ANY_THROW(Composite::Undefined().contains(Composite::Undefined()));
        EXPECT_ANY_THROW(Composite::Undefined().contains(composite));
        EXPECT_ANY_THROW(composite.contains(Composite::Undefined()));
        EXPECT_TRUE(composite.contains(point));
    }

    // Point contained in border of the Polygon, not part of the Polygon definition

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        const Point point = {0.5, 0.0};

        EXPECT_TRUE(composite.contains(point));
    }

    // Point contained in the interior of the Polygon, not part of the Polygon definition

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        const Point point = {0.5, 0.5};

        EXPECT_TRUE(composite.contains(point));
    }

    // Point contained in the border of the Polygon, but not in the LineString

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const LineString lineString = LineString({{2.0, 2.0}, {2.0, 3.0}});

        Composite composite = Composite {polygon};

        composite += Composite {lineString};

        const Point point = {1.0, 0.0};

        EXPECT_FALSE(composite.contains(point));
    }

    // Point contained in the border of the Polygon, but not in the LineString

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const LineString lineString = LineString({{2.0, 2.0}, {2.0, 3.0}});

        Composite composite = Composite {polygon};

        composite += Composite {lineString};

        const Point point = {0.5, 0.0};

        EXPECT_FALSE(composite.contains(point));
    }

    // Point contained in the border of the Polygon, and in the LineString

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const LineString lineString = LineString({{0.5, -1.0}, {0.5, 3.0}});

        Composite composite = Composite {polygon};

        composite += Composite {lineString};

        const Point point = {0.5, 0.0};

        EXPECT_TRUE(composite.contains(point));
    }

    // Point contained in the interior of the Polygon, and in the LineString

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const LineString lineString = LineString({{0.5, -1.0}, {0.5, 3.0}});

        Composite composite = Composite {polygon};

        composite += Composite {lineString};

        const Point point = {0.5, 0.5};

        EXPECT_TRUE(composite.contains(point));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, AnyContains)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Point point = {1.0, 0.0};

        EXPECT_FALSE(Composite::Empty().anyContains(point));
    }

    // Point contained in border of the Polygon as part of the Polygon definition

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        const Point point = {1.0, 0.0};

        EXPECT_ANY_THROW(Composite::Undefined().contains(Composite::Undefined()));
        EXPECT_ANY_THROW(Composite::Undefined().contains(composite));
        EXPECT_ANY_THROW(composite.contains(Composite::Undefined()));
        EXPECT_TRUE(composite.anyContains(point));
    }

    // Point contained in border of the Polygon, not part of the Polygon definition

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        const Point point = {0.5, 0.0};

        EXPECT_TRUE(composite.anyContains(point));
    }

    // Point contained in the interior of the Polygon, not part of the Polygon definition

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        const Point point = {0.5, 0.5};

        EXPECT_TRUE(composite.anyContains(point));
    }

    // Point contained in the border of the Polygon, but not in the LineString

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const LineString lineString = LineString({{2.0, 2.0}, {2.0, 3.0}});

        Composite composite = Composite {polygon};

        composite += Composite {lineString};

        const Point point = {1.0, 0.0};

        EXPECT_TRUE(composite.anyContains(point));
    }

    // Point contained in the border of the Polygon, but not in the LineString

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const LineString lineString = LineString({{2.0, 2.0}, {2.0, 3.0}});

        Composite composite = Composite {polygon};

        composite += Composite {lineString};

        const Point point = {0.5, 0.0};

        EXPECT_TRUE(composite.anyContains(point));
    }

    // Point contained in the border of the Polygon, and in the LineString

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const LineString lineString = LineString({{0.5, -1.0}, {0.5, 3.0}});

        Composite composite = Composite {polygon};

        composite += Composite {lineString};

        const Point point = {0.5, 0.0};

        EXPECT_TRUE(composite.anyContains(point));
    }

    // Point contained in the interior of the Polygon, and in the LineString

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const LineString lineString = LineString({{0.5, -1.0}, {0.5, 3.0}});

        Composite composite = Composite {polygon};

        composite += Composite {lineString};

        const Point point = {0.5, 0.5};

        EXPECT_TRUE(composite.anyContains(point));
    }

    // Point not contained in the Polygon nor in the LineString

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const LineString lineString = LineString({{0.5, -1.0}, {0.5, 3.0}});

        Composite composite = Composite {polygon};

        composite += Composite {lineString};

        const Point point = {5.0, 5.0};

        EXPECT_FALSE(composite.anyContains(point));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, Is)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        EXPECT_TRUE(composite.is<Polygon>());
        EXPECT_FALSE(composite.is<Point>());
    }

    {
        EXPECT_ANY_THROW(Composite::Undefined().is<Polygon>());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, As)
{
    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        EXPECT_EQ(polygon, composite.as<Polygon>());
        EXPECT_ANY_THROW(composite.as<Point>());
    }

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point point = {1.0, 2.0};

        Composite composite = Composite {polygon};

        const Composite otherComposite = Composite {point};

        composite += otherComposite;

        EXPECT_ANY_THROW(composite.as<Point>());
        EXPECT_ANY_THROW(composite.as<Polygon>());
        EXPECT_ANY_THROW(composite.as<LineString>());
    }

    {
        EXPECT_ANY_THROW(Composite::Undefined().as<Point>());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, AccessObjectAt)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        EXPECT_EQ(composite.accessObjectAt(0), polygon);
        EXPECT_ANY_THROW(composite.accessObjectAt(1));
    }

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point point = {1.0, 2.0};

        Composite composite = Composite {polygon};

        const Composite otherComposite = Composite {point};

        composite += otherComposite;

        EXPECT_EQ(composite.accessObjectAt(0), polygon);
        EXPECT_EQ(composite.accessObjectAt(1), point);
        EXPECT_ANY_THROW(composite.accessObjectAt(2));
    }

    {
        EXPECT_ANY_THROW(Composite::Undefined().accessObjectAt(0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, AccessObjects)
{
    using ostk::core::type::Unique;
    using ostk::core::container::Array;

    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        EXPECT_EQ(1, composite.accessObjects().getSize());
    }

    {
        EXPECT_ANY_THROW(Composite::Undefined().accessObjects());
    }

    {
        EXPECT_EQ(Array<Unique<Object>>::Empty(), Composite::Empty().accessObjects());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, GetObjectCount)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        const Composite composite = Composite {polygon};

        EXPECT_EQ(1, composite.getObjectCount());
    }

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point point = {1.0, 2.0};

        Composite composite = Composite {polygon};

        const Composite otherComposite = Composite {point};

        composite += otherComposite;
        composite += composite;

        EXPECT_EQ(4, composite.getObjectCount());
    }

    {
        EXPECT_ANY_THROW(Composite::Undefined().getObjectCount());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, ConstIterator)
{
    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point point = {1.0, 2.0};

        Composite composite = Composite {polygon};

        const Composite otherComposite = Composite {point};

        composite += otherComposite;

        EXPECT_NO_THROW(

            for (const auto& objectUPtr : composite) { EXPECT_TRUE(objectUPtr->isDefined()); }

        );
    }

    {
        EXPECT_ANY_THROW(

            for (const auto& objectUPtr : Composite::Undefined()) { (void)objectUPtr; }

        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, ApplyTransformation)
{
    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;
    using ostk::mathematics::geometry::d2::Transformation;

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        Composite composite = Composite {polygon};

        EXPECT_NO_THROW(composite.applyTransformation(Transformation::Identity()));
    }

    {
        const Polygon polygon = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

        Composite composite = Composite {polygon};

        EXPECT_ANY_THROW(composite.applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Composite::Undefined().applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Composite::Undefined().applyTransformation(Transformation::Identity()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, Undefined)
{
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        EXPECT_NO_THROW(Composite::Undefined());
        EXPECT_FALSE(Composite::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite, Empty)
{
    using ostk::mathematics::geometry::d2::object::Composite;

    {
        EXPECT_NO_THROW(Composite::Empty());
        EXPECT_TRUE(Composite::Empty().isDefined());
        EXPECT_TRUE(Composite::Empty().isEmpty());
    }
}
