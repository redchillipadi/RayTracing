#include "metal.h"

Metal::Metal(const Colour& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1.0 ? fuzz : 1.0) {}

bool Metal::scatter(const Ray& rayIn, const HitRecord& rec, Colour& attenuation, Ray& scattered) const {
    Vector3 reflected = reflect(rayIn.direction(), rec.normal);
    reflected = Normalise(reflected) + (fuzz * randomUnitVector());
    scattered = Ray(rec.point, reflected);
    attenuation = albedo;
    return (Dot(scattered.direction(), rec.normal) > 0);
}
