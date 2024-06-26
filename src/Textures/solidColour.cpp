#include "solidColour.h"

SolidColour::SolidColour() : SolidColour(Colour(0, 0, 0)) {}

SolidColour::SolidColour(const Colour& albedo) : albedo(albedo) {}

SolidColour::SolidColour(double r, double g, double b) : SolidColour(Colour(r, g, b)) {}

Colour SolidColour::value(double u, double v, const Point3& point) const {
    return albedo;
}
