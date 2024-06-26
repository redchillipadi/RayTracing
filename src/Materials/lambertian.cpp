#include "lambertian.h"
#include "../Textures/solidColour.h"

Lambertian::Lambertian(const Colour& albedo) : texture(std::make_shared<SolidColour>(albedo)) {}

Lambertian::Lambertian(std::shared_ptr<Texture> texture) : texture(texture) {}

bool Lambertian::scatter(const Ray& rayIn, const HitRecord& rec, Colour& attenuation, Ray& scattered) const {
    Vector3 scatterDirection = rec.normal + randomUnitVector();
    if (scatterDirection.NearZero())
        scatterDirection = rec.normal;

    scattered = Ray(rec.point, scatterDirection, rayIn.time());
    attenuation = texture->value(rec.u, rec.v, rec.point);
    return true;
}
