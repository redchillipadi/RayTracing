#ifndef QUAD_H
#define QUAD_H

#include "hittable.h"

class Quad : public Hittable {
public:
    /**
     * Memeberwise constructor
     * 
     * Create a quadrilateral starting at the origin, orientated with axes u and v, and using the given material
     * 
     * @param origin The origin of the quadrilateral
     * @param u The direction of the u vector
     * @param v The direction of the v vector
     * @param material The material to use
    */
    Quad(const Point3& origin, const Vector3& u, const Vector3& v, std::shared_ptr<Material> material);

    /**
     * Update the bounding box
    */
    virtual void setBoundingBox();

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

    /**
     * Are the planar coordinates within the object
     * 
     * If it is, then store the coordinates as the u and v axes in the hit Record and return true
     * Otherwise return false
     * 
     * @param alpha The planar coordinate along the u axis
     * @param beta The planar coordinate along the v axis
     * @param hitRecord Output structure to store the intersection point
     * @return True if the planar coordinates are within the object
    */
   virtual bool isInterior(double alpha, double beta, HitRecord& hitRecord) const;

private:
    Point3 origin_;
    Vector3 u_, v_, w_;
    Vector3 normal_;
    double D_;
    std::shared_ptr<Material> material_;
    AxisAlignedBoundingBox bbox_;
};

#endif