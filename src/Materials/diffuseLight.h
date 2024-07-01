#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include "material.h"
#include "../Textures/texture.h"

class DiffuseLight : public Material 
{
public:
    DiffuseLight(std::shared_ptr<Texture> texture);
    DiffuseLight(const Colour& emit);

    Colour emitted(double u, double v, const Point3& point) const override;

private:
    std::shared_ptr<Texture> texture_;
};

#endif