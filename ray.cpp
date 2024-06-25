#include "ray.h"

Ray::Ray() : originPoint{0, 0, 0}, directionVector{0, 0, 1} {}

Ray::Ray(Point3 origin, Vector3 direction)
 : originPoint(origin),
   directionVector(direction)
{}

const Point3& Ray::origin() const {
    return originPoint;
}

const Vector3& Ray::direction() const {
    return directionVector;
}


Point3 Ray::at(double t) const {
    return originPoint + t * directionVector;
}
