/// Apache License 2.0

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/srs/spheroid.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Polygon.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace planetodetic
{
namespace object
{

using BoostPoint = boost::geometry::model::point<double, 2, boost::geometry::cs::geographic<boost::geometry::degree>>;
using BoostPolygon = boost::geometry::model::polygon<BoostPoint>;
using BoostSpheroid = boost::geometry::srs::spheroid<double>;

class Polygon::Impl
{
   public:
    Impl(const Ellipsoid& anEllipsoid, const Array<Point>& anOuterRing);

    bool contains(const Point& aPoint) const;

   private:
    BoostSpheroid boostSpheroid_;
    BoostPolygon boostPolygon_;
    bool isAxisymmetricAroundPolarAxis_;
    bool isProlate_;
};

Polygon::Impl::Impl(const Ellipsoid& anEllipsoid, const Array<Point>& anOuterRing)
    : boostSpheroid_(anEllipsoid.getEquatorialRadiusA(), anEllipsoid.getPolarRadius()),
      boostPolygon_(),
      isAxisymmetricAroundPolarAxis_(anEllipsoid.getEquatorialRadiusA() == anEllipsoid.getEquatorialRadiusB()),
      isProlate_(anEllipsoid.getPolarRadius() > anEllipsoid.getEquatorialRadiusA())
{
    // Build the internal Boost polygon
    for (const auto& vertex : anOuterRing)
    {
        // Note: Boost expects (longitude, latitude) order
        boost::geometry::append(
            boostPolygon_, BoostPoint(vertex.getLongitude().inDegrees(), vertex.getLatitude().inDegrees())
        );
    }

    // Ensure the polygon is properly closed and oriented
    boost::geometry::correct(boostPolygon_);

    // Validate the polygon after correction
    std::string validityMessage;
    if (!boost::geometry::is_valid(boostPolygon_, validityMessage))
    {
        throw ostk::core::error::RuntimeError("Polygon is ill-defined, details: [{}]", validityMessage);
    }
}

bool Polygon::Impl::contains(const Point& aPoint) const
{
    if (!isAxisymmetricAroundPolarAxis_)
    {
        throw ostk::core::error::RuntimeError(
            "Contains operation is not supported for ellipsoids that are not axisymmetric around the polar axis. Try "
            "using a spheroid where equatorial radius A equals equatorial radius B."
        );
    }

    if (isProlate_)
    {
        throw ostk::core::error::RuntimeError(
            "Contains operation is not supported for prolate spheroids. Try using a sphere or an oblate spheroid "
            "(equatorial radius >= polar radius)."
        );
    }

    const BoostPoint boostPoint(aPoint.getLongitude().inDegrees(), aPoint.getLatitude().inDegrees());

    const auto strategy = boost::geometry::strategies::relate::geographic<>(boostSpheroid_);
    return boost::geometry::covered_by(boostPoint, boostPolygon_, strategy);
}

Polygon::Polygon(const Ellipsoid& anEllipsoid, const Array<Point>& anOuterRing)
    : Object(),
      ellipsoid_(anEllipsoid),
      outerRing_(anOuterRing),
      implUPtr_(nullptr)
{
    // If no vertices are provided, the polygon is undefined
    if (anOuterRing.isEmpty())
    {
        return;
    }

    for (const auto& vertex : outerRing_)
    {
        if (!vertex.isDefined())
        {
            throw ostk::core::error::RuntimeError("Polygon is ill-defined: at least one undefined vertex.");
        }
    }

    // Validate input before initialization
    if (anOuterRing.getSize() < 3)
    {
        throw ostk::core::error::RuntimeError("Polygon is ill-defined: not enough vertices (must be at least 3).");
    }

    // Check that at least one triple of consecutive points is not collinear
    bool hasNonCollinearTriple = false;
    for (Size i = 0; i < anOuterRing.getSize() - 2; ++i)
    {
        if (!anOuterRing[i].isCollinear(anOuterRing[i + 1], anOuterRing[i + 2]))
        {
            hasNonCollinearTriple = true;
            break;
        }
    }

    if (!hasNonCollinearTriple)
    {
        throw ostk::core::error::RuntimeError("Polygon is ill-defined: all points are collinear.");
    }

    this->initializeBoostGeometry();
}

Polygon::Polygon(const Polygon& aPolygon)
    : Object(aPolygon),
      ellipsoid_(aPolygon.ellipsoid_),
      outerRing_(aPolygon.outerRing_),
      implUPtr_(nullptr)
{
    this->initializeBoostGeometry();
}

Polygon::~Polygon() = default;

Polygon& Polygon::operator=(const Polygon& aPolygon)
{
    if (this != &aPolygon)
    {
        Object::operator=(aPolygon);

        ellipsoid_ = aPolygon.ellipsoid_;
        outerRing_ = aPolygon.outerRing_;

        this->initializeBoostGeometry();
    }

    return *this;
}

Polygon* Polygon::clone() const
{
    return new Polygon(*this);
}

bool Polygon::operator==(const Polygon& aPolygon) const
{
    if ((!this->isDefined()) || (!aPolygon.isDefined()))
    {
        return false;
    }

    if (ellipsoid_ != aPolygon.ellipsoid_)
    {
        return false;
    }

    if (outerRing_.getSize() != aPolygon.outerRing_.getSize())
    {
        return false;
    }

    for (Size i = 0; i < outerRing_.getSize(); ++i)
    {
        if (outerRing_[i] != aPolygon.outerRing_[i])
        {
            return false;
        }
    }

    return true;
}

bool Polygon::operator!=(const Polygon& aPolygon) const
{
    return !((*this) == aPolygon);
}

bool Polygon::isDefined() const
{
    if (!ellipsoid_.isDefined())
    {
        return false;
    }

    if (outerRing_.isEmpty())
    {
        return false;
    }

    return true;
}

bool Polygon::contains(const Point& aPoint) const
{
    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    if (implUPtr_ == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Internal implementation");
    }

    try
    {
        return implUPtr_->contains(aPoint);
    }
    catch (const std::exception& anException)
    {
        throw ostk::core::error::RuntimeError(
            "Error when checking if polygon contains point: [{}]", anException.what()
        );
    }
}

Ellipsoid Polygon::getEllipsoid() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    return ellipsoid_;
}

Size Polygon::getVertexCount() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    return outerRing_.getSize();
}

Array<Point> Polygon::getVertices() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    return outerRing_;
}

String Polygon::toString(const Object::Format& aFormat, const Integer& aPrecision) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    switch (aFormat)
    {
        case Object::Format::Standard:
        {
            String verticesString = "[";

            for (Size i = 0; i < outerRing_.getSize(); ++i)
            {
                if (aPrecision.isDefined())
                {
                    verticesString += outerRing_[i].toString(aFormat, aPrecision);
                }
                else
                {
                    verticesString += outerRing_[i].toString(aFormat);
                }

                if (i < outerRing_.getSize() - 1)
                {
                    verticesString += ", ";
                }
            }

            verticesString += "]";

            if (aPrecision.isDefined())
            {
                return String::Format(
                    "[Ellipsoid: {}, Vertices: {}]", ellipsoid_.toString(aFormat, aPrecision), verticesString
                );
            }

            return String::Format("[Ellipsoid: {}, Vertices: {}]", ellipsoid_.toString(aFormat), verticesString);
        }

        default:
            throw ostk::core::error::runtime::Wrong("Format");
    }
}

void Polygon::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Planetodetic Polygon") : void();

    ostk::core::utils::Print::Line(anOutputStream)
        << "Ellipsoid:" << (ellipsoid_.isDefined() ? ellipsoid_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream) << "Vertex count:" << outerRing_.getSize();

    if (!outerRing_.isEmpty())
    {
        ostk::core::utils::Print::Line(anOutputStream) << "Vertices:";

        for (Size i = 0; i < outerRing_.getSize(); ++i)
        {
            ostk::core::utils::Print::Line(anOutputStream)
                << "  [" << i << "]: " << (outerRing_[i].isDefined() ? outerRing_[i].toString() : "Undefined");
        }
    }

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

Polygon Polygon::Simple(const Ellipsoid& anEllipsoid, const Array<Point>& anOuterRing)
{
    return {anEllipsoid, anOuterRing};
}

Polygon Polygon::Undefined()
{
    return {Ellipsoid::Undefined(), Array<Point>::Empty()};
}

void Polygon::initializeBoostGeometry()
{
    if (this->isDefined())
    {
        implUPtr_ = std::make_unique<Polygon::Impl>(ellipsoid_, outerRing_);
    }
}

}  // namespace object
}  // namespace planetodetic
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
