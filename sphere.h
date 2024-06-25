#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "point3.h"
#include "Materials/material.h"

class Sphere : public Hittable {
public:
    /**
     * Default constructor
     * 
     * Creates a sphere at the origin with radius 1.0
    */
    Sphere();

    /**
     * Memberwise constructor for Stationary sphere
     * 
     * Creates a sphere with the given origin and radius
     * If the radius is negative it is silently set to 0.0
     * 
     * @param centre Point for the centre of the sphere
     * @param radius The radius of the sphere (>= 0)
    */
   Sphere(const Point3& centre, double radius, std::shared_ptr<Material> material);

    /**
     * Memberwise constructor for Moving sphere
     * 
     * Creates a sphere with the given origin and radius
     * If the radius is negative it is silently set to 0.0
     * 
     * @param centre1 Point for the centre of the sphere at time 0
     * @param centre2 Point for the centre of the sphere at time 1
     * @param radius The radius of the sphere (>= 0)
    */
   Sphere(const Point3& centre1, const Point3& centre2, double radius, std::shared_ptr<Material> material);

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

private:
    Point3 initial;
    Vector3 velocity;
    bool isMoving;
    double radius;
    std::shared_ptr<Material> material;

    Point3 sphereCentre(double time) const {
        return initial + time * velocity;
    }
};

#endif