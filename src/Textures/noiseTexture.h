#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H

#include "texture.h"
#include "perlin.h"

class NoiseTexture : public Texture {
public:
    /**
     * Default constructor
    */
    NoiseTexture();

    /** Memberwise constructor
     * 
     * @param scale Scaling factor to control the frequence of the noise
    */
    NoiseTexture(double scale);

    Colour value(double u, double v, const Point3& point) const override;

private:
    Perlin noise;
    double scale;
};

#endif