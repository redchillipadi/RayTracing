#include "material.h"

bool Material::scatter(const Ray& rayIn, const HitRecord& rec, Colour& attenuation, Ray& scattered) const {
    return false;
}

Colour Material::emitted(double u, double v, const Point3& point) const
{
    return Colour(0, 0, 0);
}
