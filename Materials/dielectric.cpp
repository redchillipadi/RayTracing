#include "dielectric.h"
#include "../random.h"

Dielectric::Dielectric(double refractionIndex) : refractionIndex(refractionIndex) {}

bool Dielectric::scatter(const Ray& rayIn, const HitRecord& rec, Colour& attenuation, Ray& scattered) const {
    attenuation = Colour(1.0, 1.0, 1.0);
    double refractiveIndex = rec.front ? (1.0 / refractionIndex) : refractionIndex;

    Vector3 unitDirection = Normalise(rayIn.direction());
    double cosTheta = fmin(Dot(-unitDirection, rec.normal), 1.0);
    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    bool cannotRefract = refractiveIndex * sinTheta > 1.0;
    Vector3 direction = (cannotRefract || (reflectance(cosTheta, refractionIndex) > randomDouble()))
        ? reflect(unitDirection, rec.normal)
        : refract(unitDirection, rec.normal, refractiveIndex);

    scattered = Ray(rec.point, direction);
    return true;
}

double Dielectric::reflectance(double cosine, double refractionIndex) {
    double r0 = (1.0 - refractionIndex) / (1.0 + refractionIndex);
    r0 = r0 * r0;
    return r0 + (1.0 - r0)*pow((1.0 - cosine), 5);
}
