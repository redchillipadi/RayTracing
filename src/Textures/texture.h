#ifndef TEXTURE_H
#define TEXTURE_H

#include "colour.h"
#include "../point3.h"

class Texture {
public:
    virtual ~Texture() = default;

    /**
     * Return the colour at the specified location
     * 
     * @param u Texture coordinate u
     * @param v Texture coordinate v
     * @param point The point in world coordinates
     * 
     * @return Colour at the given location
    */
    virtual Colour value(double u, double v, const Point3& point) const = 0;

private:

};

#endif