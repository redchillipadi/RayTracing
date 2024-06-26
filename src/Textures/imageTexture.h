#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include "texture.h"
#include <string>
#include <SFML/Graphics.hpp>

class ImageTexture : public Texture {
public:
    /**
     * Create an image texture from a file
     * 
     * @parama filename The name of the file to load
    */
    ImageTexture(std::string filename);

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
    sf::Texture texture;
    sf::Image image;
    int width;
    int height;
};

#endif