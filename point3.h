#ifndef POINT_3
#define POINT_3

class Vector3;

/**
 * Point class with double precision
*/
class Point3 {
public:
    /**
     * Default constructor
     * 
     * Initialises x, y and z to 0.0
    */
    Point3();

    /**
     * Memberwise Constructor
     * 
     * Sets x, y and z to specified values
     * 
     * @param x X distance
     * @param y Y distance
     * @param z Z distance
    */
    Point3(double x, double y, double z);

    /**
     * Get value of x
     * 
     * @return X distance
    */
    double x() const;

    /**
     * Get value of y
     * 
     * @return XYdistance
    */
    double y() const;

    /**
     * Get value of z
     * 
     * @return Z distance
    */
    double z() const;

    /**
     * Get distance of point from origin
    */
   double magnitude() const;

private:
    double data[3];
};

/**
 * Add a point and a vector
 * 
 * @param origin The point of origin
 * @param direction The direction vector to add
 * @return The new point at p + v
*/
Point3 operator+(const Point3& origin, const Vector3& direction);

/**
 * Subtracts a vector from a point
 * 
 * @param origin The point of origin
 * @param direction The direction vector to subtract
 * @return The new point at p - v
*/
Point3 operator-(const Point3& origin, const Vector3& direction);

/**
 * Finds a vector between two points
 * 
 * @param p1 The destination point
 * @param p2 The origin point
 * 
 * @return the vector p1 - p2
*/
Vector3 operator-(const Point3& p1, const Point3& p2);

#endif