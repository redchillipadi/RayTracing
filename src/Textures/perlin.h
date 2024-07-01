#ifndef PERLIN_H
#define PERLIN_H

#include "../point3.h"
#include "../vector3.h"
#include <vector>

class Perlin {
public:
    /**
     * Default constructor
    */
   Perlin();

    /**
     * Return noise at a given point
     * 
     * @param point The point to evaluate
     * @return Noise value
    */
    double noise(const Point3& point) const;

    /**
     * Return turbulence at a given point
     * 
     * @param point The point to evaluate
     * @param depth The depth
     * 
     * @return Turbulence value
    */
    double turbulence(const Point3& point, int depth) const;

private:
    static const int pointCount = 256;
    std::vector<Vector3> randVec;
    std::vector<int> perm_x;
    std::vector<int> perm_y;
    std::vector<int> perm_z;
    
    /**
     * Generate a randomly sorted sequence of integers
    */
    static std::vector<int> perlinGeneratePerm();

    /**
     * Shuffle all the points
     * 
     * @param point A vector of points to process
    */
    static void permute(std::vector<int>& points);

    /**
     * Smooth between the 8 surrounding points using trilinear interpolation
     * 
     * @double c An array with the surrounding points
     * @double u Coordinate of the front top left corner u
     * @double v Coordinate of the front top left corner v
     * @double w Coordinate of the front top left corner w
     * 
     * @return The interpolated value
    */
    static double perlinInterpolate(const Vector3 c[2][2][2], double u, double v, double w);
};

#endif