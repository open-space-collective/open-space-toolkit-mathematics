/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Plane.hpp>
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

Plane::Plane(const Point& aPoint, const Vector3d& aNormalVector)
    : Object(),
      point_(aPoint),
      normal_(aNormalVector.normalized())
{
}

Plane* Plane::clone() const
{
    return new Plane(*this);
}

bool Plane::operator==(const Plane& aPlane) const
{
    if ((normal_ == aPlane.normal_) || (normal_ == -aPlane.normal_))
    {
        return (point_ == aPlane.point_) || this->contains(aPlane.point_);
    }

    return false;
}

bool Plane::operator!=(const Plane& aPlane) const
{
    return !((*this) == aPlane);
}

bool Plane::intersects(const Point& aPoint) const
{
    return this->contains(aPoint);
}

bool Plane::intersects(const PointSet& aPointSet) const
{
    return (!aPointSet.isEmpty()) && std::any_of(
                                         aPointSet.begin(),
                                         aPointSet.end(),
                                         [this](const Point& aPoint) -> bool
                                         {
                                             return this->contains(aPoint);
                                         }
                                     );
}

bool Plane::intersects(const Line& aLine) const
{
    return aLine.intersects(*this);
}

bool Plane::intersects(const Ray& aRay) const
{
    return aRay.intersects(*this);
}

bool Plane::intersects(const Segment& aSegment) const
{
    return aSegment.intersects(*this);
}

bool Plane::contains(const Point& aPoint) const
{
    return (aPoint - point_).dot(normal_) == 0.0;
}

bool Plane::contains(const PointSet& aPointSet) const
{
    return (!aPointSet.isEmpty()) && std::all_of(
                                         aPointSet.begin(),
                                         aPointSet.end(),
                                         [this](const Point& aPoint) -> bool
                                         {
                                             return this->contains(aPoint);
                                         }
                                     );
}

bool Plane::contains(const Line& aLine) const
{
    return this->contains(aLine.getOrigin()) && (normal_.dot(aLine.getDirection()) == 0.0);
}

bool Plane::contains(const Ray& aRay) const
{
    return this->contains(aRay.getOrigin()) && (normal_.dot(aRay.getDirection()) == 0.0);
}

bool Plane::contains(const Segment& aSegment) const
{
    return this->contains(aSegment.getFirstPoint()) && this->contains(aSegment.getSecondPoint());
}

const Point& Plane::getPoint() const
{
    return point_;
}

const Vector3d& Plane::getNormalVector() const
{
    return normal_;
}

Intersection Plane::intersectionWith(const Point& aPoint) const
{
    return this->contains(aPoint) ? Intersection::Point(aPoint) : Intersection::Empty();
}

Intersection Plane::intersectionWith(const PointSet& aPointSet) const
{
    Array<Point> points = Array<Point>::Empty();

    for (const auto& point : aPointSet)
    {
        if (this->contains(point))
        {
            points.add(point);
        }
    }

    return (!points.isEmpty())
             ? ((points.getSize() == 1) ? Intersection::Point(points.getFirst()) : Intersection::PointSet({points}))
             : Intersection::Empty();
}

Intersection Plane::intersectionWith(const Line& aLine) const
{
    return aLine.intersectionWith(*this);
}

Intersection Plane::intersectionWith(const Ray& aRay) const
{
    return aRay.intersectionWith(*this);
}

Intersection Plane::intersectionWith(const Segment& aSegment) const
{
    return aSegment.intersectionWith(*this);
}

void Plane::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Plane") : void();

    ostk::core::utils::Print::Line(anOutputStream) << "Point:" << point_.toString();
    ostk::core::utils::Print::Line(anOutputStream) << "Normal vector:" << normal_.toString();

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

void Plane::applyTransformation(const Transformation& aTransformation)
{
    point_.applyTransformation(aTransformation);
    normal_ = aTransformation.applyTo(normal_);
}
}  // namespace object
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
