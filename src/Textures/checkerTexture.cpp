#include "checkerTexture.h"
#include "solidColour.h"
#include <memory>

CheckerTexture::CheckerTexture() : CheckerTexture(4.0, Colour(0, 0, 0), Colour(1, 1, 1)) {}

CheckerTexture::CheckerTexture(double scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd) :
    invScale(1.0 / scale),
    even(even),
    odd(odd)
{}

CheckerTexture::CheckerTexture(double scale, const Colour& colour1, const Colour& colour2) :
    invScale(1.0 / scale),
    even(std::make_shared<SolidColour>(colour1)),
    odd(std::make_shared<SolidColour>(colour2))
{}

Colour CheckerTexture::value(double u, double v, const Point3& point) const {
    int x = int(std::floor(invScale * point.x()));
    int y = int(std::floor(invScale * point.y()));
    int z = int(std::floor(invScale * point.z()));

    bool isEven = (x + y + z) % 2 == 0;

    return isEven ? even->value(u, v, point) : odd->value(u, v, point);
}

