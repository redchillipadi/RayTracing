#include "isotropic.h"

#include "../Textures/solidColour.h"

Isotropic::Isotropic(const Colour& albedo) : texture(std::make_shared<SolidColour>(albedo)) {}

Isotropic::Isotropic(std::shared_ptr<Texture>& texture) : texture(texture) {}

bool Isotropic::scatter(const Ray& rayIn, const HitRecord& rec, Colour& attenuation, Ray& scattered) const
{
    scattered = Ray(rec.point, randomUnitVector(), rayIn.time());
    attenuation = texture->value(rec.u, rec.v, rec.point);
    return true;
}
