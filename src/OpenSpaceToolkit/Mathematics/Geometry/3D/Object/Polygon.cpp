/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d3
{
namespace object
{

Polygon::Polygon(const Polygon2d& aPolygon, const Point& anOrigin, const Vector3d& aXAxis, const Vector3d& aYAxis)
    : Object(),
      polygon_(aPolygon),
      origin_(anOrigin),
      xAxis_(aXAxis.isDefined() ? aXAxis.normalized() : aXAxis),
      yAxis_(aYAxis.isDefined() ? aYAxis.normalized() : aYAxis)
{
    if (xAxis_.isDefined() && yAxis_.isDefined())
    {
        if (std::abs(xAxis_.dot(yAxis_)) > Real::Epsilon())
        {
            throw ostk::core::error::RuntimeError("X and Y axes are not orthogonal.");
        }
    }
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

    // [TBI] Implement superposition

    return (polygon_ == aPolygon.polygon_) && (origin_ == aPolygon.origin_) && (xAxis_ == aPolygon.xAxis_) &&
           (yAxis_ == aPolygon.yAxis_);
}

bool Polygon::operator!=(const Polygon& aPolygon) const
{
    return !((*this) == aPolygon);
}

bool Polygon::isDefined() const
{
    return polygon_.isDefined() && origin_.isDefined() && xAxis_.isDefined() && yAxis_.isDefined();
}

bool Polygon::isNear(const Polygon& aPolygon, const Real& aTolerance) const
{
    if (!aPolygon.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    if (!aTolerance.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Tolerance");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    if (this->getVertexCount() != aPolygon.getVertexCount())
    {
        return false;
    }

    const Array<Polygon::Vertex> firstVertices = this->getVertices();
    const Array<Polygon::Vertex> secondVertices = aPolygon.getVertices();

    // for (const auto vertexTuple : ostk::core::container::iterator::Zip(this->getVertices(), aPolygon.getVertices()))
    for (const auto vertexTuple : ostk::core::container::iterator::Zip(firstVertices, secondVertices))
    {
        if (!std::get<0>(vertexTuple).isNear(std::get<1>(vertexTuple), aTolerance))
        {
            return false;
        }
    }

    return true;
}

Polygon2d Polygon::getPolygon2d() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    return polygon_;
}

Point Polygon::getOrigin() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    return origin_;
}

Vector3d Polygon::getXAxis() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    return xAxis_;
}

Vector3d Polygon::getYAxis() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    return yAxis_;
}

Vector3d Polygon::getNormalVector() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    return xAxis_.cross(yAxis_).normalized();
}

Size Polygon::getEdgeCount() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    return polygon_.getEdgeCount();
}

Size Polygon::getVertexCount() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    return polygon_.getVertexCount();
}

Polygon::Edge Polygon::getEdgeAt(const Index anEdgeIndex) const
{
    using Point2d = ostk::mathematics::geometry::d2::object::Point;
    using Segment2d = ostk::mathematics::geometry::d2::object::Segment;

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    const Segment2d edge2d = polygon_.getEdgeAt(anEdgeIndex);

    const Point2d& firstVertex2d = edge2d.getFirstPoint();
    const Point2d& secondVertex2d = edge2d.getSecondPoint();

    const Point firstVertex = origin_ + ((firstVertex2d.x() * xAxis_) + (firstVertex2d.y() * yAxis_));
    const Point secondVertex = origin_ + ((secondVertex2d.x() * xAxis_) + (secondVertex2d.y() * yAxis_));

    return {firstVertex, secondVertex};
}

Polygon::Vertex Polygon::getVertexAt(const Index aVertexIndex) const
{
    using Point2d = ostk::mathematics::geometry::d2::object::Point;

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    const Point2d vertex2d = polygon_.getVertexAt(aVertexIndex);

    return origin_ + ((vertex2d.x() * xAxis_) + (vertex2d.y() * yAxis_));
}

Array<Polygon::Edge> Polygon::getEdges() const
{
    using Point2d = ostk::mathematics::geometry::d2::object::Point;

    Array<Polygon::Edge> edges = Array<Polygon::Edge>::Empty();

    edges.reserve(polygon_.getEdgeCount());

    for (const auto& edge2d : polygon_.getEdges())
    {
        const Point2d& firstVertex2d = edge2d.getFirstPoint();
        const Point2d& secondVertex2d = edge2d.getSecondPoint();

        const Point firstVertex = origin_ + ((firstVertex2d.x() * xAxis_) + (firstVertex2d.y() * yAxis_));
        const Point secondVertex = origin_ + ((secondVertex2d.x() * xAxis_) + (secondVertex2d.y() * yAxis_));

        edges.add(Polygon::Edge(firstVertex, secondVertex));
    }

    return edges;
}

Array<Polygon::Vertex> Polygon::getVertices() const
{
    Array<Polygon::Vertex> vertices = Array<Polygon::Vertex>::Empty();

    vertices.reserve(polygon_.getVertexCount());

    for (const auto& vertex2d : polygon_.getVertices())
    {
        vertices.add(origin_ + ((vertex2d.x() * xAxis_) + (vertex2d.y() * yAxis_)));
    }

    return vertices;
}

// Intersection                    Polygon::intersectionWith                      (   const   Polygon& aPolygon ) const
// {

// }

void Polygon::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Polygon") : void();

    ostk::core::utils::Print::Line(anOutputStream)
        << "Origin:" << (origin_.isDefined() ? origin_.toString() : "Undefined");

    ostk::core::utils::Print::Line(anOutputStream)
        << "X axis:" << (xAxis_.isDefined() ? xAxis_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Y axis:" << (yAxis_.isDefined() ? yAxis_.toString() : "Undefined");

    ostk::core::utils::Print::Separator(anOutputStream, "Polygon");

    polygon_.print(anOutputStream, false);

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

void Polygon::applyTransformation(const Transformation& aTransformation)
{
    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Polygon");
    }

    // polygon_ = aTransformation.applyTo(polygon_) ;

    origin_ = aTransformation.applyTo(origin_);

    xAxis_ = aTransformation.applyTo(xAxis_);
    yAxis_ = aTransformation.applyTo(yAxis_);
}

Polygon Polygon::Undefined()
{
    return {Polygon2d::Undefined(), Point::Undefined(), Vector3d::Undefined(), Vector3d::Undefined()};
}

}  // namespace object
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
