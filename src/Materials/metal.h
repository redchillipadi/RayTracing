#ifndef METAL_H
#define METAL_H

#include "material.h"

class Metal : public Material {
public:
    Metal(const Colour& albedo, double fuzz);

    bool scatter(const Ray& rayIn, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override;

private:
    Colour albedo;
    double fuzz;
};

#endif