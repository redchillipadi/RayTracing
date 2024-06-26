#ifndef SOLID_COLOUR_H
#define SOLID_COLOUR_H

#include "texture.h"

class SolidColour : public Texture {
public:
    /**
     * Default constructor
     * 
     * Create a black colour
    */
    SolidColour();

    /**
     * Alternate constructor
     * 
     * Create solid colour from the colour provided
    */
    SolidColour(const Colour& albedo);

    /**
     * Alternate constructor
     * 
     * Create solid colour from the RGB values provided
    */
    SolidColour(double r, double g, double b);

    /**
     * Return the colour at the specified location
     * 
     * @param u Texture coordinate u
     * @param v Texture coordinate v
     * @param point The point in world coordinates
     * 
     * @return Colour at the given location
    */
    Colour value(double u, double v, const Point3& point) const override;

private:
    Colour albedo;
};

#endif