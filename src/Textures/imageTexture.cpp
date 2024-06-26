#include "imageTexture.h"
#include <iostream>
#include "../interval.h"

ImageTexture::ImageTexture(std::string filename) {
    width = 0;
    height = 0;

    if (!texture.loadFromFile(filename)) {
        std::cerr << "Unable to load file " << filename << std::endl;
        return;
    }
    image = texture.copyToImage();
    image.flipVertically();

    width = image.getSize().x;
    height = image.getSize().y;

}

Colour ImageTexture::value(double u, double v, const Point3& point) const {
    if (height <= 0)
        return Colour(0, 1, 1);

    int i = Interval(0, width-1).clamp(u * width);
    int j = Interval(0, height-1).clamp(v * height);

    sf::Color colour = image.getPixel(i, j);
    double colourScale = 1.0 / 255.0;

    return Colour(colourScale * colour.r, colourScale * colour.g, colourScale * colour.b);
}

