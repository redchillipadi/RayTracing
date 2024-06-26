#ifndef CAMERA_H
#define CAMERA_H

#include "Shapes/hittable.h"
#include "Shapes/hittableList.h"
#include "colour.h"
#include <SFML/Graphics.hpp>

/**
 * Set the colour of a pixel in the pixel buffer
 * 
 * The pixel buffer must have already been created, and should be in RGBA format
 * 
 * @param pixels Array of pixel data (not null)
 * @param width Width of the pixel buffer (> 0)
 * @param height Height of the pixel buffer (> 0)
 * @param x X index of the pixel to set (0 <= x < width)
 * @param y Y index of the pixel to set (0 <= y < height)
 * @param colour The colour of the pixel
 * 
 * @return true if the pixel was set, otherwise false
 */
bool setPixel(sf::Uint8* pixels, int width, int height, int x, int y, Colour colour);

class Camera {
public:
    /**
     * Default constructor
    */
   Camera();

   /**
    * Memberwise constructor
    * 
    * @param width The width of the image in pixels
    * @param height The height of the image in pixels
    * @param samplesPerPixel The number of samples to make for each pixel
    * @param maxDepth The maximum number of bounces for a ray
   */
  Camera(int width, int height, int samplesPerPixel, int maxDepth);

    /**
     * Render the world as viewed from the camera
     * 
     * @params world Contains the objects to render
    */
    void render(const Hittable& world, sf::Uint8* pixels);

    /**
     * Set the vertical field of view
     * 
     * @param angle Vertical FOV in degrees
    */
    void setVFOV(double angle);

    /**
     * Set the aperture to control defocus blur (depth of field)
     * 
     * @param angle The defocus angle
     * @param distance The focus distance
    */
   void setAperture(double angle, double distance);

    /**
     * Set the camera position and orientation
     * 
     * @param lookFrom World coordinates of the camera origin
     * @param lookAt World coordinates of the target
     * @param viewUp The direction of up
    */
   void setOrientation(const Point3& lookFrom, const Point3& lookAt, const Vector3& viewUp);

private:
    double aspectRatio;
    int width;
    int height;
    int samplesPerPixel;
    double pixelSamplesScale;
    Point3 centre;
    Point3 pixel00;
    Vector3 pixelDeltaU;
    Vector3 pixelDeltaV;
    int maxDepth;
    double vfov;
    Point3 lookFrom;
    Point3 lookAt;
    Vector3 viewUp, u, v, w;
    double defocusAngle, focusDistance;
    Vector3 defocusDiskU, defocusDiskV;

    int currentX, currentY;

    /**
     * Initialise the camera settings
     * 
     * Called at the beginning of each render
    */
    void initialise();

    /**
     * Do the ray tracing and return the colour of the ray
     * 
     * @param ray The ray to test
     * @param dpeth The number of bounces remaining
     * @param world Contains the objects to render
     * @return The colour of the ray 
    */
    Colour rayColour(const Ray& ray, int depth, const Hittable& world) const;


    /**
     * Return a ray from the camera to a random point around the pixel x, y
     * 
     * @param x The pixel's x offset in screen space
     * @param y The pixel's y offset in screen space
    */
    Ray getRay(int x, int y) const;

    /**
     * Return the offset to a random point within a unit square centred on the origin
     * 
     * @return A vector to the randomly selected point
    */
    Vector3 sampleSquare() const;

    /**
     * Sample from defocus disk
     * 
     * @return A random point in the defocus disk
    */
   Point3 defocusDiskSample() const;
};

#endif