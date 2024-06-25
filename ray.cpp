#include "ray.h"

Ray::Ray() : originPoint{0, 0, 0}, directionVector{0, 0, 1}, tm(0) {}

Ray::Ray(Point3 origin, Vector3 direction, double time)
 : originPoint(origin),
   directionVector(direction),
   tm(time)
{}

const Point3& Ray::origin() const {
    return originPoint;
}

const Vector3& Ray::direction() const {
    return directionVector;
}

double Ray::time() const {
    return tm;
}


Point3 Ray::at(double t) const {
    return originPoint + t * directionVector;
}
