/// Apache License 2.0

#include <cmath>

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
      xAxis_(aXAxis.normalized()),
      yAxis_(aYAxis.normalized())
{
    if (std::abs(xAxis_.dot(yAxis_)) > 1e-15)
    {
        throw ostk::core::error::RuntimeError("X and Y axes are not orthogonal.");
    }
}

Polygon* Polygon::clone() const
{
    return new Polygon(*this);
}

bool Polygon::operator==(const Polygon& aPolygon) const
{
    // [TBI] Implement superposition

    return (polygon_ == aPolygon.polygon_) && (origin_ == aPolygon.origin_) && (xAxis_ == aPolygon.xAxis_) &&
           (yAxis_ == aPolygon.yAxis_);
}

bool Polygon::operator!=(const Polygon& aPolygon) const
{
    return !((*this) == aPolygon);
}

bool Polygon::isNear(const Polygon& aPolygon, double aTolerance) const
{
    if (std::isnan(aTolerance))
    {
        throw ostk::core::error::runtime::Undefined("Tolerance");
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

const Polygon2d& Polygon::getPolygon2d() const
{
    return polygon_;
}

const Point& Polygon::getOrigin() const
{
    return origin_;
}

const Vector3d& Polygon::getXAxis() const
{
    return xAxis_;
}

const Vector3d& Polygon::getYAxis() const
{
    return yAxis_;
}

Vector3d Polygon::getNormalVector() const
{
    return xAxis_.cross(yAxis_).normalized();
}

Size Polygon::getEdgeCount() const
{
    return polygon_.getEdgeCount();
}

Size Polygon::getVertexCount() const
{
    return polygon_.getVertexCount();
}

Polygon::Edge Polygon::getEdgeAt(const Index anEdgeIndex) const
{
    using Point2d = ostk::mathematics::geometry::d2::object::Point;
    using Segment2d = ostk::mathematics::geometry::d2::object::Segment;

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

    ostk::core::utils::Print::Line(anOutputStream) << "Origin:" << origin_.toString();

    ostk::core::utils::Print::Line(anOutputStream) << "X axis:" << xAxis_.toString();
    ostk::core::utils::Print::Line(anOutputStream) << "Y axis:" << yAxis_.toString();

    ostk::core::utils::Print::Separator(anOutputStream, "Polygon");

    polygon_.print(anOutputStream, false);

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

void Polygon::applyTransformation(const Transformation& aTransformation)
{
    // polygon_ = aTransformation.applyTo(polygon_) ;

    origin_ = aTransformation.applyTo(origin_);

    xAxis_ = aTransformation.applyTo(xAxis_);
    yAxis_ = aTransformation.applyTo(yAxis_);
}
}  // namespace object
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
