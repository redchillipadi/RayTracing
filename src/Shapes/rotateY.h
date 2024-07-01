#ifndef ROTATE_Y
#define ROTATE_Y

#include "hittable.h"

class RotateY : public Hittable
{
public:
    /**
     * Memberwise constructor
     * 
     * @param object The object to rotate
     * @param angle The angle to rotate around the Y axis in degrees
    */
   RotateY(std::shared_ptr<Hittable> object, double angle);

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
    double sinTheta;
    double cosTheta;
    AxisAlignedBoundingBox bbox;
};

#endif