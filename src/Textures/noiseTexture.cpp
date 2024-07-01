#include "noiseTexture.h"
#include "../vector3.h"

NoiseTexture::NoiseTexture() : scale(1) {}

NoiseTexture::NoiseTexture(double scale) : scale(scale) {}

Colour NoiseTexture::value(double u, double v, const Point3& point) const {
    return Colour(0.5, 0.5, 0.5) * (1.0 + sin(scale * point.z() + 10.0 * noise.turbulence(point, 7)));
}
