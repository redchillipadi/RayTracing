#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Shapes/hittable.h"
#include "../Textures/colour.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& rayIn, const HitRecord& rec, Colour& attenuation, Ray& scattered) const;

private:

};

#endif