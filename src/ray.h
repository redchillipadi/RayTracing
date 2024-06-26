#ifndef RAY_H
#define RAY_H

#include "point3.h"
#include "vector3.h"

class Ray {
public:
    /**
     * Default constructor
     * 
     * Creates a ray from the origin facing forwards
    */
    Ray();

    /**
     * Memberwise constructor
     * 
     * @param origin The point where the ray starts
     * @param direction The direction the ray extends
     * @param tm The time the ray was cast
    */
   Ray(Point3 origin, Vector3 direction, double time);

    /**
     * Get the origin point
     * 
     * @return The point the ray originates from
    */
    const Point3& origin() const;

    /**
     * Get the direction
     * 
     * @return The direction the ray extends
    */
   const Vector3& direction() const;

  /**
   * Get the point at a given distance along the ray
   * 
   * @param t The distance from the origin
   * 
   * @return p = o + t * v
  */
  Point3 at(double t) const;

  /**
   * Get the time the ray was cast
   * 
   * @return The time
  */
 double time() const;

private:
    Point3 originPoint;
    Vector3 directionVector;
    double tm;
};

#endif