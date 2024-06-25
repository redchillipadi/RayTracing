#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class Lambertian : public Material {
public:
    Lambertian(const Colour& albedo);

    bool scatter(const Ray& rayIn, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override;

private:
    Colour albedo;
};

#endif