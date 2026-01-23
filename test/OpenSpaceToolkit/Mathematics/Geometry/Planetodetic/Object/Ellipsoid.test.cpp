/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Ellipsoid.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::mathematics::geometry::planetodetic::object::Ellipsoid;

class OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid : public ::testing::Test
{
   protected:
    const Real equatorialRadiusA_ = Real(1100.0);
    const Real equatorialRadiusB_ = Real(1200.0);
    const Real polarRadius_ = Real(1000.0);
    const Real differentEquatorialRadiusA_ = Real(1400.0);
    const Real differentEquatorialRadiusB_ = Real(1300.0);
    const Real differentPolarRadius_ = Real(1500.0);
    const Real flattening_ = 0.1;

    const Ellipsoid ellipsoid_ = Ellipsoid(equatorialRadiusA_, equatorialRadiusB_, polarRadius_);
    const Ellipsoid differentEllipsoid_ =
        Ellipsoid(differentEquatorialRadiusA_, differentEquatorialRadiusB_, differentPolarRadius_);
};

struct SpheroidFailureTestParams
{
    Real equatorialRadius;
    Real flattening;
    Real polarRadius;
};

class OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid_SpheroidFailure
    : public ::testing::TestWithParam<SpheroidFailureTestParams>
{
};

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, Constructor)
{
    {
        EXPECT_NO_THROW(Ellipsoid(equatorialRadiusA_, equatorialRadiusB_, polarRadius_));
    }

    {
        EXPECT_THROW(
            try {
                Ellipsoid(0.0, equatorialRadiusB_, polarRadius_);
            } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Equatorial radius A") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }

    {
        EXPECT_THROW(
            try {
                Ellipsoid(-1000.0, equatorialRadiusB_, polarRadius_);
            } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Equatorial radius A") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }

    {
        EXPECT_THROW(
            try {
                Ellipsoid(equatorialRadiusA_, 0.0, polarRadius_);
            } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Equatorial radius B") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }

    {
        EXPECT_THROW(
            try {
                Ellipsoid(equatorialRadiusA_, -1000.0, polarRadius_);
            } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Equatorial radius B") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }

    {
        EXPECT_THROW(
            try {
                Ellipsoid(equatorialRadiusA_, equatorialRadiusB_, 0.0);
            } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Polar radius") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }

    {
        EXPECT_THROW(
            try {
                Ellipsoid(equatorialRadiusA_, equatorialRadiusB_, -1000.0);
            } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Polar radius") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, Clone)
{
    {
        const Ellipsoid* clonedEllipsoidPtr = ellipsoid_.clone();

        EXPECT_EQ(ellipsoid_, *clonedEllipsoidPtr);

        delete clonedEllipsoidPtr;
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, EqualToOperator)
{
    {
        EXPECT_TRUE(ellipsoid_ == ellipsoid_);
    }

    {
        EXPECT_FALSE(ellipsoid_ == differentEllipsoid_);
    }

    {
        EXPECT_TRUE(
            ellipsoid_ ==
            Ellipsoid(ellipsoid_.getEquatorialRadiusA(), ellipsoid_.getEquatorialRadiusB(), ellipsoid_.getPolarRadius())
        );
        EXPECT_FALSE(
            ellipsoid_ == Ellipsoid(
                              differentEllipsoid_.getEquatorialRadiusA(),
                              ellipsoid_.getEquatorialRadiusB(),
                              ellipsoid_.getPolarRadius()
                          )
        );
        EXPECT_FALSE(
            ellipsoid_ == Ellipsoid(
                              ellipsoid_.getEquatorialRadiusA(),
                              differentEllipsoid_.getEquatorialRadiusB(),
                              ellipsoid_.getPolarRadius()
                          )
        );
        EXPECT_FALSE(
            ellipsoid_ == Ellipsoid(
                              ellipsoid_.getEquatorialRadiusA(),
                              ellipsoid_.getEquatorialRadiusB(),
                              differentEllipsoid_.getPolarRadius()
                          )
        );
    }

    {
        EXPECT_FALSE(ellipsoid_ == Ellipsoid::Undefined());
        EXPECT_FALSE(Ellipsoid::Undefined() == ellipsoid_);
        EXPECT_FALSE(Ellipsoid::Undefined() == Ellipsoid::Undefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, NotEqualToOperator)
{
    {
        EXPECT_FALSE(ellipsoid_ != ellipsoid_);
    }

    {
        EXPECT_TRUE(ellipsoid_ != differentEllipsoid_);
    }

    {
        EXPECT_FALSE(
            ellipsoid_ !=
            Ellipsoid(ellipsoid_.getEquatorialRadiusA(), ellipsoid_.getEquatorialRadiusB(), ellipsoid_.getPolarRadius())
        );
        EXPECT_TRUE(
            ellipsoid_ != Ellipsoid(
                              differentEllipsoid_.getEquatorialRadiusA(),
                              ellipsoid_.getEquatorialRadiusB(),
                              ellipsoid_.getPolarRadius()
                          )
        );
        EXPECT_TRUE(
            ellipsoid_ != Ellipsoid(
                              ellipsoid_.getEquatorialRadiusA(),
                              differentEllipsoid_.getEquatorialRadiusB(),
                              ellipsoid_.getPolarRadius()
                          )
        );
        EXPECT_TRUE(
            ellipsoid_ != Ellipsoid(
                              ellipsoid_.getEquatorialRadiusA(),
                              ellipsoid_.getEquatorialRadiusB(),
                              differentEllipsoid_.getPolarRadius()
                          )
        );
    }

    {
        EXPECT_TRUE(ellipsoid_ != Ellipsoid::Undefined());
        EXPECT_TRUE(Ellipsoid::Undefined() != ellipsoid_);
        EXPECT_TRUE(Ellipsoid::Undefined() != Ellipsoid::Undefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << ellipsoid_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, IsDefined)
{
    {
        EXPECT_TRUE(ellipsoid_.isDefined());
    }

    {
        EXPECT_FALSE(Ellipsoid::Undefined().isDefined());
    }

    {
        EXPECT_FALSE(Ellipsoid(Real::Undefined(), equatorialRadiusB_, polarRadius_).isDefined());
    }

    {
        EXPECT_FALSE(Ellipsoid(equatorialRadiusA_, Real::Undefined(), polarRadius_).isDefined());
    }

    {
        EXPECT_FALSE(Ellipsoid(equatorialRadiusA_, equatorialRadiusB_, Real::Undefined()).isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, GetEquatorialRadiusA)
{
    {
        EXPECT_EQ(equatorialRadiusA_, ellipsoid_.getEquatorialRadiusA());
    }

    {
        EXPECT_THROW(
            try {
                Ellipsoid::Undefined().getEquatorialRadiusA();
            } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, GetEquatorialRadiusB)
{
    {
        EXPECT_EQ(equatorialRadiusB_, ellipsoid_.getEquatorialRadiusB());
    }

    {
        EXPECT_THROW(
            try {
                Ellipsoid::Undefined().getEquatorialRadiusB();
            } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, GetPolarRadius)
{
    {
        EXPECT_EQ(polarRadius_, ellipsoid_.getPolarRadius());
    }

    {
        EXPECT_THROW(
            try { Ellipsoid::Undefined().getPolarRadius(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, ToString)
{
    {
        const Ellipsoid& ellipsoid = ellipsoid_;

        EXPECT_FALSE(ellipsoid.toString().empty());
        EXPECT_FALSE(ellipsoid.toString(Ellipsoid::Format::Standard).empty());
    }

    {
        const Ellipsoid& ellipsoid = ellipsoid_;

        EXPECT_FALSE(ellipsoid.toString(Ellipsoid::Format::Standard, 10).empty());
    }

    {
        const Ellipsoid& ellipsoid = ellipsoid_;
        const String str = ellipsoid.toString();

        EXPECT_TRUE(std::string(str).find(equatorialRadiusA_.toString()) != std::string::npos);
        EXPECT_TRUE(std::string(str).find(polarRadius_.toString()) != std::string::npos);
    }

    {
        EXPECT_NO_THROW(Ellipsoid::Undefined().toString());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, Undefined)
{
    {
        EXPECT_NO_THROW(Ellipsoid::Undefined());
        EXPECT_FALSE(Ellipsoid::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, Sphere)
{
    {
        const Ellipsoid sphere = Ellipsoid::Sphere(equatorialRadiusA_);

        EXPECT_TRUE(sphere.isDefined());
        EXPECT_EQ(equatorialRadiusA_, sphere.getEquatorialRadiusA());
        EXPECT_EQ(equatorialRadiusA_, sphere.getEquatorialRadiusB());
        EXPECT_EQ(equatorialRadiusA_, sphere.getPolarRadius());
    }

    {
        EXPECT_THROW(
            try { Ellipsoid::Sphere(0.0); } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Equatorial radius") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }

    {
        EXPECT_THROW(
            try { Ellipsoid::Sphere(-1000.0); } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Equatorial radius") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, Spheroid)
{
    {
        const Ellipsoid spheroid = Ellipsoid::Spheroid(equatorialRadiusA_, flattening_);

        EXPECT_TRUE(spheroid.isDefined());
        EXPECT_EQ(equatorialRadiusA_, spheroid.getEquatorialRadiusA());
        EXPECT_EQ(equatorialRadiusA_, spheroid.getEquatorialRadiusB());
        EXPECT_NEAR(equatorialRadiusA_ * (1.0 - flattening_), spheroid.getPolarRadius(), 1e-6);
    }

    {
        const Ellipsoid spheroid = Ellipsoid::Spheroid(equatorialRadiusA_, Real::Undefined(), polarRadius_);

        EXPECT_TRUE(spheroid.isDefined());
        EXPECT_EQ(equatorialRadiusA_, spheroid.getEquatorialRadiusA());
        EXPECT_EQ(equatorialRadiusA_, spheroid.getEquatorialRadiusB());
        EXPECT_EQ(polarRadius_, spheroid.getPolarRadius());
    }

    {
        const Ellipsoid spheroid = Ellipsoid::Spheroid(Real::Undefined(), flattening_, polarRadius_);

        EXPECT_TRUE(spheroid.isDefined());
        EXPECT_NEAR(polarRadius_ / (1.0 - flattening_), spheroid.getEquatorialRadiusA(), 1e-6);
        EXPECT_NEAR(polarRadius_ / (1.0 - flattening_), spheroid.getEquatorialRadiusB(), 1e-6);
        EXPECT_EQ(polarRadius_, spheroid.getPolarRadius());
    }
}

INSTANTIATE_TEST_SUITE_P(
    SpheroidFailureCases,
    OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid_SpheroidFailure,
    ::testing::Values(
        // Too many arguments
        SpheroidFailureTestParams {1100.0, 0.1, 1000.0},
        // Too few arguments
        SpheroidFailureTestParams {Real::Undefined(), Real::Undefined(), Real::Undefined()},
        SpheroidFailureTestParams {1100.0, Real::Undefined(), Real::Undefined()},
        SpheroidFailureTestParams {Real::Undefined(), 0.1, Real::Undefined()},
        SpheroidFailureTestParams {Real::Undefined(), Real::Undefined(), 1000.0},
        // Degenerate spheroids
        SpheroidFailureTestParams {0.0, 0.1, Real::Undefined()},
        SpheroidFailureTestParams {-1000.0, 0.1, Real::Undefined()},
        SpheroidFailureTestParams {1100.0, 1.0, Real::Undefined()},
        SpheroidFailureTestParams {1100.0, 2.0, Real::Undefined()},
        SpheroidFailureTestParams {Real::Undefined(), 0.1, 0.0},
        SpheroidFailureTestParams {Real::Undefined(), 0.1, -1000.0},
        SpheroidFailureTestParams {Real::Undefined(), 1.0, 1000.0},
        SpheroidFailureTestParams {Real::Undefined(), 2.0, 1000.0},
        SpheroidFailureTestParams {0.0, Real::Undefined(), 1000.0},
        SpheroidFailureTestParams {-1000.0, Real::Undefined(), 1000.0},
        SpheroidFailureTestParams {1100.0, Real::Undefined(), 0.0},
        SpheroidFailureTestParams {1100.0, Real::Undefined(), -1000.0},
        SpheroidFailureTestParams {1100.0, 0.1, 1000.0}
    )
);

TEST_P(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid_SpheroidFailure, Failures)
{
    const auto& params = GetParam();

    EXPECT_ANY_THROW(Ellipsoid::Spheroid(params.equatorialRadius, params.flattening, params.polarRadius));
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid, WGS84)
{
    {
        const Ellipsoid wgs84 = Ellipsoid::WGS84();

        EXPECT_TRUE(wgs84.isDefined());
        EXPECT_EQ(6378137.0, wgs84.getEquatorialRadiusA());
        EXPECT_EQ(6378137.0, wgs84.getEquatorialRadiusB());
        EXPECT_NEAR(6356752.314245, wgs84.getPolarRadius(), 1e-6);
    }
}
