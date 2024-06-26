#ifndef BOUNDING_VOLUME_HIERARCHY_H
#define BOUNDING_VOLUME_HIERARCHY_H

#include "axisAlignedBoundingBox.h"
#include "hittable.h"
#include "hittableList.h"

class BoundingVolumeHierarchyNode : public Hittable {
public:
    /**
     * Create a BVH from a HittableList
     * 
     * @param list a HittableList containing the objects
    */
    BoundingVolumeHierarchyNode(HittableList list);

    /**
     * Create a BVH from a vector of shared Hittable object pointers
     * 
     * @param objects A vector containing the objects
     * @param start Starting index in the vector
     * @param end One past the last object in the vector
    */
    BoundingVolumeHierarchyNode(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end);

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
    std::shared_ptr<Hittable> left;
    std::shared_ptr<Hittable> right;
    AxisAlignedBoundingBox bbox;

    static bool boxCompare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, int axis);
    static bool boxCompareX(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b);
    static bool boxCompareY(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b);
    static bool boxCompareZ(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b);

};

#endif