#include "diffuseLight.h"
#include "../Textures/solidColour.h"

DiffuseLight::DiffuseLight(std::shared_ptr<Texture> texture) : texture_(texture) {}

DiffuseLight::DiffuseLight(const Colour& emit) : texture_(std::make_shared<SolidColour>(emit)) {}

Colour DiffuseLight::emitted(double u, double v, const Point3& point) const
{
    return texture_->value(u, v, point);
}
