#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>
#include "hittable.h"

class HittableList : public Hittable {
public:
    /**
     * Default constuctor
     * 
     * Start with an empty list
    */
    HittableList();

    /**
     * Create and initialise with an existing object
     * 
     * @param object The object to place in the list
    */
    HittableList(std::shared_ptr<Hittable> object);

    /**
     * Clear all objects in the list
    */
    void clear();

    /**
     * Add a new object to the list
     * 
     * @param object The object to add to the list
    */
    void add(std::shared_ptr<Hittable> object);

    /**
     * Determines whether the ray hits any object
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
     * Return the AABB tightly surrounding the shapes
     * 
     * @return The Axis Aligned Bounding Box
    */
    AxisAlignedBoundingBox boundingBox() const override; 

    /**
     * Return access to the underlying vector of shared Hittable objects
     * 
     * @return The objects vector
    */
    std::vector<std::shared_ptr<Hittable>>& objectVector();


private:
    std::vector<std::shared_ptr<Hittable>> objects;
    AxisAlignedBoundingBox bbox;

};

#endif