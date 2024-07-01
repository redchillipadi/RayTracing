#ifndef AXIS_ALIGNED_BOUNDING_BOX_H
#define AXIS_ALIGNED_BOUNDING_BOX_H

#include "../interval.h"
#include "../ray.h"

class AxisAlignedBoundingBox {
public:
    /**
     * Default constructor
     * 
     * Create an empty AABB
    */
    AxisAlignedBoundingBox();

    /**
     * Memberwise constructor
     * 
     * Create an AABB with the given intervals
     * @param x The interval on the x axis
     * @param y The interval on the y axis
     * @param z The interval on the z axis
    */
    AxisAlignedBoundingBox(const Interval& x, const Interval& y, const Interval& z);

    /**
     * Alternative constructor
     * 
     * Create an AABB covering the volume enclosed by two points
     * @param p1 The first point
     * @param p2 The second point
    */
   AxisAlignedBoundingBox(const Point3& p1, const Point3& p2);

   /**
    * Alternative constructor
    * 
    * Create an AABB tightly enclosing the two given AABB
    * @param aabb1 The first AABB
    * @param aabb2 The second AABB
   */
   AxisAlignedBoundingBox(const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2);

    /**
     * Get the interval using an index
     * 
     * If the index is invalid, return the x axis interval
     * 
     * @param n The interval to obtain (x = 0, y = 1, z = 2)
     * @return The specified interval
    */
   const Interval& axisInterval(int n) const;

    /**
     * Return true if the given ray intersects the AABB and provide the time of contact
     * 
     * This occurs if there is a overlap between the time the ray intersects the slabs on each axis
     * 
     * @param ray The ray to test
     * @param interval Output the time interval the ray intersects the AABB
     * 
     * @return True if the ray intersects the AABB
    */
    bool hit(const Ray& ray, Interval interval) const;

    /**
     * Return the index of the longest axis in the bounding box
     * 
     * @return The index of the longest axis
    */
    int longestAxis() const;

    /**
     * The empty AABB contains empty intervals
    */
    static const AxisAlignedBoundingBox empty;
    
    /**
     * The universe AABB contains intervals from -inf to +inf on all axes
     */
    static const AxisAlignedBoundingBox universe;

private:
    Interval x, y, z;

    /**
     * Pad the AABB so that no side is narrower than delta
    */
    void padToMinimums();
};

AxisAlignedBoundingBox operator+(const AxisAlignedBoundingBox& aabb, const Vector3& v);

#endif