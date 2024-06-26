#ifndef CHECKER_TEXTURE_H
#define CHECKER_TEXTURE_H

#include "texture.h"
#include <memory>

class CheckerTexture : public Texture {
public:
    /**
     * Default constructor
     * 
     * Create a black and white texture of scale 4.0
    */
    CheckerTexture();

    /**
     * Alternative constructor
     * 
     * Create a checker texture from the given textures
     * 
     * @param scale The scale for the size of the squares
     * @param even The texture to display in even squares
     * @param odd The texture to display in odd squares
    */
    CheckerTexture(double scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);

    /**
     * Alternative constructor
     * 
     * Create a checker texture from the given colours
     * 
     * @param scale The scale for the size of the squares
     * @param even The colour to display in even squares
     * @param odd The colour to display in odd squares
    */
    CheckerTexture(double scale, const Colour& colour1, const Colour& colour2);

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
    double invScale;
    std::shared_ptr<Texture> even;
    std::shared_ptr<Texture> odd;    
};

#endif