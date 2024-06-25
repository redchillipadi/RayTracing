#ifndef HITTABLE_H
#define HITTABLE_H

#include "point3.h"
#include "vector3.h"
#include "ray.h"
#include "interval.h"
#include <memory>

class Material;

/**
 * Stores information about where a ray hits the object
*/
struct HitRecord {
    Point3 point;
    Vector3 normal;
    double t;
    bool front;
    std::shared_ptr<Material> material;

    void setNormal(const Ray& ray, const Vector3& normal);
};

/**
 * Interface for objects which can be hit by a ray
*/
class Hittable {
public:
    virtual ~Hittable() = default;

    /**
     * Determines whether the ray hits the object
     * 
     * A hit is valid only if it hits between tMin and tMax along hte ray.
     * 
     * @param ray The ray to test.
     * @param hitRecord Output variable to set when the ray hits the object
     * 
     * @return true if the object is hit by the ray
    */
    virtual bool Hit(const Ray& ray, Interval interval, HitRecord& hitRecord) const = 0;

private:

};

#endif