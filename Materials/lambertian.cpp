#include "lambertian.h"

Lambertian::Lambertian(const Colour& albedo) : albedo(albedo) {}

bool Lambertian::scatter(const Ray& rayIn, const HitRecord& rec, Colour& attenuation, Ray& scattered) const {
    Vector3 scatterDirection = rec.normal + randomUnitVector();
    if (scatterDirection.NearZero())
        scatterDirection = rec.normal;

    scattered = Ray(rec.point, scatterDirection, rayIn.time());
    attenuation = albedo;
    return true;
}
