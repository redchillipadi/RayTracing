#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "hittable.h"

class Translate : public Hittable
{
public:
    /**
     * Memberwise constructor
     * 
     * @param object The object to translate
     * @param offset The vector by which to translate the object
    */
   Translate(std::shared_ptr<Hittable> object, const Vector3& offset);

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
    bool Hit(const Ray& ray, Interval interval, HitRecord& hitRecord) const override;

    /**
     * Return the AABB surrounding the shape
     * 
     * @return The Axis Aligned Bounding Box
    */
    AxisAlignedBoundingBox boundingBox() const override; 

private:
    std::shared_ptr<Hittable> object;
    Vector3 offset;
    AxisAlignedBoundingBox bbox;
};

#endif