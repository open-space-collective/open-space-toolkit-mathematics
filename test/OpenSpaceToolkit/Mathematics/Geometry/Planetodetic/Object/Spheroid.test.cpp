/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Spheroid.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::mathematics::geometry::planetodetic::object::Spheroid;

class OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid : public ::testing::Test
{
   protected:
    const Real equatorialRadius_ = Real(6378137.0);
    const Real flattening_ = Real(1.0 / 298.257223563);
    const Real differentEquatorialRadius_ = Real(6000000.0);
    const Real differentFlattening_ = Real(0.01);

    const Spheroid spheroid_ = Spheroid::FromEquatorialRadiusAndFlattening(equatorialRadius_, flattening_);
    const Spheroid differentSpheroid_ =
        Spheroid::FromEquatorialRadiusAndFlattening(differentEquatorialRadius_, differentFlattening_);
};

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, Clone)
{
    {
        EXPECT_NO_THROW(const Spheroid* spheroidPtr = spheroid_.clone(); delete spheroidPtr;);
    }

    {
        const Spheroid* clonedSpheroidPtr = spheroid_.clone();

        EXPECT_EQ(spheroid_, *clonedSpheroidPtr);

        delete clonedSpheroidPtr;
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, EqualToOperator)
{
    {
        EXPECT_TRUE(spheroid_ == spheroid_);
    }

    {
        EXPECT_FALSE(spheroid_ == differentSpheroid_);
    }

    {
        EXPECT_FALSE(spheroid_ == Spheroid::FromEquatorialRadiusAndFlattening(equatorialRadius_, differentFlattening_));
    }

    {
        EXPECT_TRUE(
            Spheroid::Sphere(equatorialRadius_) == Spheroid::FromEquatorialRadiusAndFlattening(equatorialRadius_, 0.0)
        );
    }

    {
        EXPECT_FALSE(spheroid_ == Spheroid::Undefined());
        EXPECT_FALSE(Spheroid::Undefined() == spheroid_);
        EXPECT_FALSE(Spheroid::Undefined() == Spheroid::Undefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, NotEqualToOperator)
{
    {
        EXPECT_FALSE(spheroid_ != spheroid_);
    }

    {
        EXPECT_TRUE(spheroid_ != differentSpheroid_);
    }

    {
        EXPECT_TRUE(spheroid_ != Spheroid::FromEquatorialRadiusAndFlattening(equatorialRadius_, differentFlattening_));
    }

    {
        EXPECT_FALSE(
            Spheroid::Sphere(equatorialRadius_) != Spheroid::FromEquatorialRadiusAndFlattening(equatorialRadius_, 0.0)
        );
    }

    {
        EXPECT_TRUE(spheroid_ != Spheroid::Undefined());
        EXPECT_TRUE(Spheroid::Undefined() != spheroid_);
        EXPECT_TRUE(Spheroid::Undefined() != Spheroid::Undefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << spheroid_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, IsDefined)
{
    {
        EXPECT_TRUE(spheroid_.isDefined());
    }

    {
        EXPECT_TRUE(Spheroid::Sphere(equatorialRadius_).isDefined());
    }

    {
        EXPECT_FALSE(Spheroid::Undefined().isDefined());
    }

    {
        EXPECT_FALSE(Spheroid::FromEquatorialRadiusAndFlattening(Real::Undefined(), flattening_).isDefined());
    }

    {
        EXPECT_FALSE(Spheroid::FromEquatorialRadiusAndFlattening(equatorialRadius_, Real::Undefined()).isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, GetEquatorialRadius)
{
    {
        const Spheroid& spheroid = spheroid_;

        EXPECT_EQ(equatorialRadius_, spheroid.getEquatorialRadius());
    }

    {
        EXPECT_THROW(
            try {
                Spheroid::Undefined().getEquatorialRadius();
            } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, GetPolarRadius)
{
    {
        const Spheroid& spheroid = spheroid_;
        const Real expectedPolarRadius = equatorialRadius_ * (1.0 - flattening_);

        EXPECT_EQ(expectedPolarRadius, spheroid.getPolarRadius());
    }

    {
        const Spheroid sphere = Spheroid::Sphere(equatorialRadius_);

        EXPECT_EQ(equatorialRadius_, sphere.getPolarRadius());
    }

    {
        const Real prolateFlattening = Real(-0.1);
        const Spheroid prolateSpheroid =
            Spheroid::FromEquatorialRadiusAndFlattening(equatorialRadius_, prolateFlattening);
        const Real expectedPolarRadius = equatorialRadius_ * (1.0 - prolateFlattening);

        EXPECT_EQ(expectedPolarRadius, prolateSpheroid.getPolarRadius());
        EXPECT_GT(prolateSpheroid.getPolarRadius(), prolateSpheroid.getEquatorialRadius());
    }

    {
        EXPECT_THROW(
            try { Spheroid::Undefined().getPolarRadius(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, GetFlattening)
{
    {
        const Spheroid& spheroid = spheroid_;

        EXPECT_EQ(flattening_, spheroid.getFlattening());
    }

    {
        const Spheroid sphere = Spheroid::Sphere(equatorialRadius_);

        EXPECT_EQ(0.0, sphere.getFlattening());
    }

    {
        EXPECT_THROW(
            try { Spheroid::Undefined().getFlattening(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, GetEccentricity)
{
    {
        const Spheroid& spheroid = spheroid_;
        const Real eccentricity = spheroid.getEccentricity();

        EXPECT_TRUE(eccentricity.isDefined());
        EXPECT_GT(eccentricity, 0.0);
        EXPECT_LT(eccentricity, 1.0);
    }

    {
        const Spheroid sphere = Spheroid::Sphere(equatorialRadius_);

        EXPECT_EQ(0.0, sphere.getEccentricity());
    }

    {
        EXPECT_THROW(
            try { Spheroid::Undefined().getEccentricity(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, IsOblate)
{
    {
        const Spheroid& spheroid = spheroid_;

        EXPECT_TRUE(spheroid.isOblate());
    }

    {
        const Spheroid sphere = Spheroid::Sphere(equatorialRadius_);

        EXPECT_FALSE(sphere.isOblate());
    }

    {
        const Spheroid prolateSpheroid = Spheroid::FromEquatorialRadiusAndFlattening(equatorialRadius_, -0.1);

        EXPECT_FALSE(prolateSpheroid.isOblate());
    }

    {
        EXPECT_THROW(
            try { Spheroid::Undefined().isOblate(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, IsProlate)
{
    {
        const Spheroid& spheroid = spheroid_;

        EXPECT_FALSE(spheroid.isProlate());
    }

    {
        const Spheroid sphere = Spheroid::Sphere(equatorialRadius_);

        EXPECT_FALSE(sphere.isProlate());
    }

    {
        const Spheroid prolateSpheroid = Spheroid::FromEquatorialRadiusAndFlattening(equatorialRadius_, -0.1);

        EXPECT_TRUE(prolateSpheroid.isProlate());
    }

    {
        EXPECT_THROW(
            try { Spheroid::Undefined().isProlate(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, IsSphere)
{
    {
        const Spheroid& spheroid = spheroid_;

        EXPECT_FALSE(spheroid.isSphere());
    }

    {
        const Spheroid sphere = Spheroid::Sphere(equatorialRadius_);

        EXPECT_TRUE(sphere.isSphere());
    }

    {
        const Spheroid prolateSpheroid = Spheroid::FromEquatorialRadiusAndFlattening(equatorialRadius_, -0.1);

        EXPECT_FALSE(prolateSpheroid.isSphere());
    }

    {
        EXPECT_THROW(
            try { Spheroid::Undefined().isSphere(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, ToString)
{
    {
        const Spheroid& spheroid = spheroid_;

        EXPECT_FALSE(spheroid.toString().empty());
        EXPECT_FALSE(spheroid.toString(Spheroid::Format::Standard).empty());
    }

    {
        const Spheroid& spheroid = spheroid_;

        EXPECT_FALSE(spheroid.toString(Spheroid::Format::Standard, 10).empty());
    }

    {
        const Spheroid& spheroid = spheroid_;
        const String str = spheroid.toString();

        EXPECT_TRUE(std::string(str).find(equatorialRadius_.toString()) != std::string::npos);
        EXPECT_TRUE(std::string(str).find(flattening_.toString()) != std::string::npos);
    }

    {
        EXPECT_NO_THROW(Spheroid::Undefined().toString());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, Undefined)
{
    {
        EXPECT_NO_THROW(Spheroid::Undefined());
        EXPECT_FALSE(Spheroid::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, Sphere)
{
    {
        const Spheroid sphere = Spheroid::Sphere(equatorialRadius_);

        EXPECT_TRUE(sphere.isDefined());
        EXPECT_EQ(equatorialRadius_, sphere.getEquatorialRadius());
        EXPECT_EQ(equatorialRadius_, sphere.getPolarRadius());
        EXPECT_EQ(0.0, sphere.getFlattening());
        EXPECT_EQ(0.0, sphere.getEccentricity());
        EXPECT_TRUE(sphere.isSphere());
        EXPECT_FALSE(sphere.isOblate());
        EXPECT_FALSE(sphere.isProlate());
    }

    {
        EXPECT_THROW(
            try { Spheroid::Sphere(0.0); } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Equatorial radius") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }

    {
        EXPECT_THROW(
            try { Spheroid::Sphere(-1000.0); } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Equatorial radius") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid, FromEquatorialRadiusAndFlattening)
{
    {
        const Spheroid spheroid = Spheroid::FromEquatorialRadiusAndFlattening(equatorialRadius_, flattening_);

        EXPECT_TRUE(spheroid.isDefined());
        EXPECT_EQ(equatorialRadius_, spheroid.getEquatorialRadius());
        EXPECT_EQ(flattening_, spheroid.getFlattening());
        EXPECT_EQ(equatorialRadius_ * (1.0 - flattening_), spheroid.getPolarRadius());
        EXPECT_EQ(std::sqrt(2.0 * flattening_ - flattening_ * flattening_), spheroid.getEccentricity());
        EXPECT_FALSE(spheroid.isSphere());
        EXPECT_TRUE(spheroid.isOblate());
        EXPECT_FALSE(spheroid.isProlate());
    }

    {
        EXPECT_THROW(
            try {
                Spheroid::FromEquatorialRadiusAndFlattening(0.0, flattening_);
            } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Equatorial radius") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }

    {
        EXPECT_THROW(
            try {
                Spheroid::FromEquatorialRadiusAndFlattening(-1000.0, flattening_);
            } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Equatorial radius") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }

    {
        EXPECT_THROW(
            try {
                Spheroid::FromEquatorialRadiusAndFlattening(equatorialRadius_, 1.0);
            } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Flattening") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }

    {
        EXPECT_THROW(
            try {
                Spheroid::FromEquatorialRadiusAndFlattening(equatorialRadius_, 2.0);
            } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Flattening") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }
}
