#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include "hittable.h"
#include "../Materials/material.h"
#include "../Textures/texture.h"

class ConstantMedium : public Hittable
{
public:
    /**
     * Memberwise constructor
     * 
     * @param boundary Any object describing the boundaries of the medium
     * @param density The density of the medium
     * @param texture Texture to use for display
    */
    ConstantMedium(std::shared_ptr<Hittable> boundary, double density, std::shared_ptr<Texture> texture);

    /**
     * Memberwise constructor
     * 
     * @param boundary Any object describing the boundaries of the medium
     * @param density The density of the medium
     * @param albedo Albedo to use for display
    */
    ConstantMedium(std::shared_ptr<Hittable> boundary, double density, const Colour& albedo);

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
    std::shared_ptr<Hittable> boundary;
    double negInvDensity;
    std::shared_ptr<Material> phaseFunction;

};

#endif