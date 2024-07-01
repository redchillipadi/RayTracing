#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include "material.h"
#include "../Textures/texture.h"

class Isotropic : public Material
{
public:
    Isotropic(const Colour& albedo);

    Isotropic(std::shared_ptr<Texture>& texture);

    bool scatter(const Ray& rayIn, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override;

private:
    std::shared_ptr<Texture> texture;
    
};

#endif