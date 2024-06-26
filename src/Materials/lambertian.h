#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "../Textures/texture.h"
#include <memory>

class Lambertian : public Material {
public:
    /**
     * Memberwise constructor
     * 
     * Create a lambertian given a colour
     * 
     * @param albedo The colour parameter
    */
    Lambertian(const Colour& albedo);

    /**
     * Memberwise constructor
     * 
     * Create a lambertian given a texture
     * 
     * @param texture The texture to use
    */
    Lambertian(std::shared_ptr<Texture> texture);

    bool scatter(const Ray& rayIn, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override;

private:
    std::shared_ptr<Texture> texture;
};

#endif