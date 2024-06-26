#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"

class Dielectric : public Material {
public:
    Dielectric(double refractionIndex);

    virtual bool scatter(const Ray& rayIn, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override;

private:
    double refractionIndex;

    /**
     * Schlick's approximation for reflectance
     * 
     * @param cosine Angle of incidence compared to normal
     * @param refractionIndex Ratio of refractive indices (eta / eta')
    */
    static double reflectance(double cosine, double refractionIndex);
};

#endif