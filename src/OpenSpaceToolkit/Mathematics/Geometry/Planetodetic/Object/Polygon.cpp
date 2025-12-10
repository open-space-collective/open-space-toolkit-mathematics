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
    Impl(const Spheroid& aSpheroid, const Array<Point>& anOuterRing);

    bool contains(const Point& aPoint) const;

   private:
    BoostSpheroid boostSpheroid_;
    BoostPolygon boostPolygon_;
};

Polygon::Impl::Impl(const Spheroid& aSpheroid, const Array<Point>& anOuterRing)
    : boostSpheroid_(aSpheroid.getEquatorialRadius(), aSpheroid.getPolarRadius()),
      boostPolygon_()
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
    const BoostPoint boostPoint(aPoint.getLongitude().inDegrees(), aPoint.getLatitude().inDegrees());

    const auto strategy = boost::geometry::strategies::relate::geographic<>(boostSpheroid_);
    return boost::geometry::covered_by(boostPoint, boostPolygon_, strategy);
}

Polygon::Polygon(const Spheroid& aSpheroid, const Array<Point>& anOuterRing)
    : Object(),
      spheroid_(aSpheroid),
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
      spheroid_(aPolygon.spheroid_),
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

        spheroid_ = aPolygon.spheroid_;
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

    if (spheroid_ != aPolygon.spheroid_)
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
    if (!spheroid_.isDefined())
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

    if (spheroid_.isProlate())
    {
        throw ostk::core::error::RuntimeError("Internal implementation does not support prolate spheroids.");
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

Spheroid Polygon::getSpheroid() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    return spheroid_;
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
                    "[Spheroid: {}, Vertices: {}]", spheroid_.toString(aFormat, aPrecision), verticesString
                );
            }

            return String::Format("[Spheroid: {}, Vertices: {}]", spheroid_.toString(aFormat), verticesString);
        }

        default:
            throw ostk::core::error::runtime::Wrong("Format");
    }
}

void Polygon::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Planetodetic Polygon") : void();

    ostk::core::utils::Print::Line(anOutputStream)
        << "Spheroid:" << (spheroid_.isDefined() ? spheroid_.toString() : "Undefined");
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

Polygon Polygon::Simple(const Spheroid& aSpheroid, const Array<Point>& anOuterRing)
{
    return {aSpheroid, anOuterRing};
}

Polygon Polygon::Undefined()
{
    return {Spheroid::Undefined(), Array<Point>::Empty()};
}

void Polygon::initializeBoostGeometry()
{
    if (this->isDefined())
    {
        implUPtr_ = std::make_unique<Polygon::Impl>(spheroid_, outerRing_);
    }
}

}  // namespace object
}  // namespace planetodetic
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
