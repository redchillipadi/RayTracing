#include "camera.h"
#include "Materials/material.h"
#include "random.h"
#include <math.h>
#include <iostream>

double linearToGamma(double linear)
{
    return (linear > 0.0) ? sqrt(linear) : 0.0;
}

double degreesToRadians(double degrees)
{
    return degrees * M_PI / 180.0;
}

bool setPixel(sf::Uint8* pixels, int width, int height, int x, int y, Colour colour)
{
    if (pixels == nullptr || x < 0 || x >= width || y < 0 || y >= height)
        return false;

    static const Interval intensity(0.000, 0.9999);

    pixels[(width*y+x)*4+0] = int(256 * intensity.clamp(linearToGamma(colour.r())));
    pixels[(width*y+x)*4+1] = int(256 * intensity.clamp(linearToGamma(colour.g())));
    pixels[(width*y+x)*4+2] = int(256 * intensity.clamp(linearToGamma(colour.b())));
    pixels[(width*y+x)*4+3] = 0xff;

    return true;
}

Camera::Camera()
 :  width(600),
    height(600),
    aspectRatio(1.0),
    samplesPerPixel(10),
    maxDepth(10),
    vfov(90),
    lookFrom(Point3(0, 0, 0)),
    lookAt(Point3(0, 0, -1)),
    viewUp(Vector3(0, 1, 0)),
    defocusAngle(0),
    focusDistance(10),
    currentX(0),
    currentY(0)
{}

Camera::Camera(int width, int height, int samplesPerPixel, int maxDepth)
 :  width(width),
    height(height),
    aspectRatio(double(width)/double(height)),
    samplesPerPixel(samplesPerPixel),
    maxDepth(maxDepth),
    vfov(90),
    lookFrom(Point3(0, 0, 0)),
    lookAt(Point3(0, 0, -1)),
    viewUp(Vector3(0, 1, 0)),
    defocusAngle(0),
    focusDistance(10),
    currentX(0),
    currentY(0)
{}

void Camera::setOrientation(const Point3& lookFrom, const Point3& lookAt, const Vector3& viewUp) {
    this->lookFrom = lookFrom;
    this->lookAt = lookAt;
    this->viewUp = viewUp;
}

void Camera::render(const Hittable& world, sf::Uint8* pixels) {
    initialise();

    int y = currentY;

    for (int x=0; x<width; x++) {

    Colour pixelColour(0, 0, 0);
    for (int sample = 0; sample < samplesPerPixel; sample++) {
        Ray ray = getRay(x, y);
        pixelColour += rayColour(ray, maxDepth, world);
    }
    setPixel(pixels, width, height, x, y, pixelSamplesScale * pixelColour);

    }

    currentY = (currentY + 1) % height;
}

void Camera::initialise() {
    pixelSamplesScale = 1.0 / samplesPerPixel;
    centre = lookFrom;
    
    double theta = degreesToRadians(vfov);
    double h = tan(theta/2.0);
    double viewportHeight = 2.0 * h * focusDistance;
    double viewportWidth = viewportHeight * (double(width)/double(height));

    w = Normalise(lookFrom - lookAt);
    u = Normalise(Cross(viewUp, w));
    v = Cross(w, u); 

    Vector3 viewportU = viewportWidth * u;
    Vector3 viewportV = viewportHeight * -v;
    pixelDeltaU = viewportU / width;
    pixelDeltaV = viewportV / height;
    Point3 viewport00 = centre - (focusDistance * w) - viewportU/2.0 - viewportV/2.0;
    pixel00 = viewport00 + 0.5 * (pixelDeltaU + pixelDeltaV);

    double defocusRadius = focusDistance * tan(degreesToRadians(defocusAngle / 2.0));
    defocusDiskU = u * defocusRadius;
    defocusDiskV = v * defocusRadius;
}

Colour Camera::rayColour(const Ray& ray, int depth, const Hittable& world) const {
    HitRecord rec;

    if (depth <=0)
        return Colour(0, 0, 0);

    if (world.Hit(ray, Interval(0.001, infinity), rec)) {
        Ray scattered;
        Colour attenuation;

        if (rec.material->scatter(ray, rec, attenuation, scattered))
            return attenuation * rayColour(scattered, depth-1, world);
        else
            return Colour(0, 0, 0);
    }

    Vector3 direction = Normalise(ray.direction());
    double a = 0.5 * (direction.y() + 1.0);
    return (1.0 - a) * Colour(1.0, 1.0, 1.0) + a * Colour(0.5, 0.7, 1.0);
}

Ray Camera::getRay(int x, int y) const {
    Vector3 offset = sampleSquare();
    Point3 pixelLocation = pixel00 + ((x + offset.x()) * pixelDeltaU) + ((y + offset.y()) * pixelDeltaV);
    Point3 rayOrigin = (defocusAngle <= 0) ? centre : defocusDiskSample();
    Vector3 direction = pixelLocation - rayOrigin;
    double rayTime = randomDouble();
    return Ray(centre, direction, rayTime);
}

Vector3 Camera::sampleSquare() const {
    return Vector3(randomDouble() - 0.5, randomDouble() - 0.5, 0.0);
}

void Camera::setVFOV(double angle) {
    vfov = angle;
}

Point3 Camera::defocusDiskSample() const {
    Vector3 point = randomInUnitDisk();
    return centre + (point.x() * defocusDiskU) + (point.y() * defocusDiskV);
}

void Camera::setAperture(double angle, double distance)
{
    defocusAngle = angle;
    focusDistance = distance;
}

