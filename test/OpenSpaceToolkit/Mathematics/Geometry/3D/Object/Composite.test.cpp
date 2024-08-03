/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Composite.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Cuboid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, Constructor)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        EXPECT_NO_THROW(Composite composite(pyramid););
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex);

        EXPECT_NO_THROW(Composite composite(pyramidUPtr););
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex);

        const Point center = {0.0, 0.0, 0.0};
        const std::array<Vector3d, 3> axes = {
            Vector3d {1.0, 0.0, 0.0}, Vector3d {0.0, 1.0, 0.0}, Vector3d {0.0, 0.0, 1.0}
        };
        const std::array<Real, 3> extent = {1.0, 2.0, 3.0};

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent);

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty();

        objects.emplace_back(std::move(pyramidUPtr));
        objects.emplace_back(std::move(cuboidUPtr));

        EXPECT_NO_THROW(Composite composite(std::move(objects)););
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, Clone)
{
    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        EXPECT_NO_THROW(const Composite* compositePtr = Composite(pyramid).clone(); delete compositePtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, CopyConstructor)
{
    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_NO_THROW(Composite otherComposite(composite););
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, EqualToOperator)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_TRUE(composite == composite);
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex);

        const Point center = {0.0, 0.0, 0.0};
        const std::array<Vector3d, 3> axes = {
            Vector3d {1.0, 0.0, 0.0}, Vector3d {0.0, 1.0, 0.0}, Vector3d {0.0, 0.0, 1.0}
        };
        const std::array<Real, 3> extent = {1.0, 2.0, 3.0};

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent);

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty();

        objects.emplace_back(std::move(pyramidUPtr));
        objects.emplace_back(std::move(cuboidUPtr));

        const Composite composite = Composite {std::move(objects)};

        EXPECT_TRUE(composite == composite);
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite firstComposite = Composite {pyramid};

        const Point center = {0.0, 0.0, 0.0};
        const std::array<Vector3d, 3> axes = {
            Vector3d {1.0, 0.0, 0.0}, Vector3d {0.0, 1.0, 0.0}, Vector3d {0.0, 0.0, 1.0}
        };
        const std::array<Real, 3> extent = {1.0, 2.0, 3.0};

        const Cuboid cuboid = {center, axes, extent};

        const Composite secondComposite = Composite {cuboid};

        EXPECT_FALSE(firstComposite == secondComposite);
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex);

        const Point center = {0.0, 0.0, 0.0};
        const std::array<Vector3d, 3> axes = {
            Vector3d {1.0, 0.0, 0.0}, Vector3d {0.0, 1.0, 0.0}, Vector3d {0.0, 0.0, 1.0}
        };
        const std::array<Real, 3> extent = {1.0, 2.0, 3.0};

        const Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent);

        Array<Unique<Object>> firstObjects = Array<Unique<Object>>::Empty();

        firstObjects.emplace_back(std::move(pyramidUPtr->clone()));
        firstObjects.emplace_back(std::move(cuboidUPtr->clone()));

        const Composite firstComposite = Composite {std::move(firstObjects)};

        Array<Unique<Object>> secondObjects = Array<Unique<Object>>::Empty();

        secondObjects.emplace_back(std::move(cuboidUPtr->clone()));
        secondObjects.emplace_back(std::move(pyramidUPtr->clone()));

        const Composite secondComposite = Composite {std::move(secondObjects)};

        EXPECT_FALSE(firstComposite == secondComposite);
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_FALSE(Composite::Undefined() == Composite::Undefined());
        EXPECT_FALSE(Composite::Undefined() == composite);
        EXPECT_FALSE(composite == Composite::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, NotEqualToOperator)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_FALSE(composite != composite);
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex);

        const Point center = {0.0, 0.0, 0.0};
        const std::array<Vector3d, 3> axes = {
            Vector3d {1.0, 0.0, 0.0}, Vector3d {0.0, 1.0, 0.0}, Vector3d {0.0, 0.0, 1.0}
        };
        const std::array<Real, 3> extent = {1.0, 2.0, 3.0};

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent);

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty();

        objects.emplace_back(std::move(pyramidUPtr));
        objects.emplace_back(std::move(cuboidUPtr));

        const Composite composite = Composite {std::move(objects)};

        EXPECT_FALSE(composite != composite);
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite firstComposite = Composite {pyramid};

        const Point center = {0.0, 0.0, 0.0};
        const std::array<Vector3d, 3> axes = {
            Vector3d {1.0, 0.0, 0.0}, Vector3d {0.0, 1.0, 0.0}, Vector3d {0.0, 0.0, 1.0}
        };
        const std::array<Real, 3> extent = {1.0, 2.0, 3.0};

        const Cuboid cuboid = {center, axes, extent};

        const Composite secondComposite = Composite {cuboid};

        EXPECT_TRUE(firstComposite != secondComposite);
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex);

        const Point center = {0.0, 0.0, 0.0};
        const std::array<Vector3d, 3> axes = {
            Vector3d {1.0, 0.0, 0.0}, Vector3d {0.0, 1.0, 0.0}, Vector3d {0.0, 0.0, 1.0}
        };
        const std::array<Real, 3> extent = {1.0, 2.0, 3.0};

        const Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent);

        Array<Unique<Object>> firstObjects = Array<Unique<Object>>::Empty();

        firstObjects.emplace_back(std::move(pyramidUPtr->clone()));
        firstObjects.emplace_back(std::move(cuboidUPtr->clone()));

        const Composite firstComposite = Composite {std::move(firstObjects)};

        Array<Unique<Object>> secondObjects = Array<Unique<Object>>::Empty();

        secondObjects.emplace_back(std::move(cuboidUPtr->clone()));
        secondObjects.emplace_back(std::move(pyramidUPtr->clone()));

        const Composite secondComposite = Composite {std::move(secondObjects)};

        EXPECT_TRUE(firstComposite != secondComposite);
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_TRUE(Composite::Undefined() != Composite::Undefined());
        EXPECT_TRUE(Composite::Undefined() != composite);
        EXPECT_TRUE(composite != Composite::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, AdditionOperator)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_NO_THROW(composite + composite);
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        Composite composite = Composite {pyramid};

        EXPECT_ANY_THROW(Composite::Undefined() + composite);
        EXPECT_ANY_THROW(composite + Composite::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, AdditionAssignmentOperator)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        Composite composite = Composite {pyramid};

        EXPECT_NO_THROW(composite += composite);
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        Composite composite = Composite {pyramid};

        EXPECT_ANY_THROW(Composite::Undefined() += composite);
        EXPECT_ANY_THROW(composite += Composite::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, StreamOperator)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << composite << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, IsDefined)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_TRUE(composite.isDefined());
    }

    {
        EXPECT_FALSE(Composite::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, IsEmpty)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_FALSE(composite.isEmpty());
    }

    {
        EXPECT_TRUE(Composite::Empty().isEmpty());
    }

    {
        EXPECT_ANY_THROW(Composite::Undefined().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, Intersects)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    // [TBI]

    // {

    //     const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 },
    //     { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ; const Point apex = { 0.0, 0.0, 1.0 } ;

    //     const Pyramid pyramid = { base, apex } ;

    //     const Composite composite = Composite { pyramid } ;

    //     EXPECT_TRUE(composite.intersects(composite)) ;

    // }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_ANY_THROW(Composite::Undefined().intersects(Composite::Undefined()));
        EXPECT_ANY_THROW(Composite::Undefined().intersects(composite));
        EXPECT_ANY_THROW(composite.intersects(Composite::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, Contains)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    // [TBI]

    // {

    //     const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 },
    //     { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ; const Point apex = { 0.0, 0.0, 1.0 } ;

    //     const Pyramid pyramid = { base, apex } ;

    //     const Composite composite = Composite { pyramid } ;

    //     EXPECT_TRUE(composite.contains(composite)) ;

    // }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_ANY_THROW(Composite::Undefined().contains(Composite::Undefined()));
        EXPECT_ANY_THROW(Composite::Undefined().contains(composite));
        EXPECT_ANY_THROW(composite.contains(Composite::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, Is)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_TRUE(composite.is<Pyramid>());

        EXPECT_FALSE(composite.is<Cuboid>());
    }

    {
        EXPECT_ANY_THROW(Composite::Undefined().is<Pyramid>());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, As)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_EQ(pyramid, composite.as<Pyramid>());

        EXPECT_ANY_THROW(composite.as<Cuboid>());
    }

    {
        EXPECT_ANY_THROW(Composite::Undefined().as<Pyramid>());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, AccessObjectAt)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_TRUE(composite.accessObjectAt(0).is<Pyramid>());

        EXPECT_ANY_THROW(composite.accessObjectAt(1));
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex);

        const Point center = {0.0, 0.0, 0.0};
        const std::array<Vector3d, 3> axes = {
            Vector3d {1.0, 0.0, 0.0}, Vector3d {0.0, 1.0, 0.0}, Vector3d {0.0, 0.0, 1.0}
        };
        const std::array<Real, 3> extent = {1.0, 2.0, 3.0};

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent);

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty();

        objects.emplace_back(std::move(pyramidUPtr));
        objects.emplace_back(std::move(cuboidUPtr));

        const Composite composite = Composite {std::move(objects)};

        EXPECT_TRUE(composite.accessObjectAt(0).is<Pyramid>());
        EXPECT_TRUE(composite.accessObjectAt(1).is<Cuboid>());

        EXPECT_ANY_THROW(composite.accessObjectAt(2));
    }

    {
        EXPECT_ANY_THROW(Composite::Undefined().accessObjectAt(0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, AccessObjects)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_EQ(1, composite.accessObjects().getSize());
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex);

        const Point center = {0.0, 0.0, 0.0};
        const std::array<Vector3d, 3> axes = {
            Vector3d {1.0, 0.0, 0.0}, Vector3d {0.0, 1.0, 0.0}, Vector3d {0.0, 0.0, 1.0}
        };
        const std::array<Real, 3> extent = {1.0, 2.0, 3.0};

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent);

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty();

        objects.emplace_back(std::move(pyramidUPtr));
        objects.emplace_back(std::move(cuboidUPtr));

        const Composite composite = Composite {std::move(objects)};

        EXPECT_EQ(2, composite.accessObjects().getSize());
    }

    {
        EXPECT_ANY_THROW(Composite::Undefined().accessObjects());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, GetObjectCount)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_EQ(1, composite.getObjectCount());
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex);

        const Point center = {0.0, 0.0, 0.0};
        const std::array<Vector3d, 3> axes = {
            Vector3d {1.0, 0.0, 0.0}, Vector3d {0.0, 1.0, 0.0}, Vector3d {0.0, 0.0, 1.0}
        };
        const std::array<Real, 3> extent = {1.0, 2.0, 3.0};

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent);

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty();

        objects.emplace_back(std::move(pyramidUPtr));
        objects.emplace_back(std::move(cuboidUPtr));

        const Composite composite = Composite {std::move(objects)};

        EXPECT_EQ(2, composite.getObjectCount());
    }

    {
        EXPECT_ANY_THROW(Composite::Undefined().getObjectCount());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, ConstIterator)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Composite composite = Composite {pyramid};

        EXPECT_NO_THROW(

            for (const auto& objectUPtr : composite) { EXPECT_TRUE(objectUPtr->isDefined()); }

        );
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex);

        const Point center = {0.0, 0.0, 0.0};
        const std::array<Vector3d, 3> axes = {
            Vector3d {1.0, 0.0, 0.0}, Vector3d {0.0, 1.0, 0.0}, Vector3d {0.0, 0.0, 1.0}
        };
        const std::array<Real, 3> extent = {1.0, 2.0, 3.0};

        Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent);

        Array<Unique<Object>> objects = Array<Unique<Object>>::Empty();

        objects.emplace_back(std::move(pyramidUPtr));
        objects.emplace_back(std::move(cuboidUPtr));

        const Composite composite = Composite {std::move(objects)};

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

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, ApplyTransformation)
{
    using ostk::core::type::Unique;
    using ostk::core::type::Real;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;
    using ostk::mathematics::geometry::d3::Transformation;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        Composite composite = Composite {pyramid};

        EXPECT_NO_THROW(composite.applyTransformation(Transformation::Identity()));
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        Composite composite = Composite {pyramid};

        EXPECT_ANY_THROW(composite.applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Composite::Undefined().applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Composite::Undefined().applyTransformation(Transformation::Identity()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, Undefined)
{
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        EXPECT_NO_THROW(Composite::Undefined());
        EXPECT_FALSE(Composite::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite, Empty)
{
    using ostk::mathematics::geometry::d3::object::Composite;

    {
        EXPECT_NO_THROW(Composite::Empty());
        EXPECT_TRUE(Composite::Empty().isDefined());
        EXPECT_TRUE(Composite::Empty().isEmpty());
    }
}
