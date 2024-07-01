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
     * Alternate constructor
     * 
     * Create point from a vector
     * 
     * @param vector The vector to convert
    */
   Point3(const Vector3& vector);

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
     * Get value of the given axis by index
     * 
     * Return the x axis if the index is invalid
     * 
     * @param n The axis to retrieve (x=0, y=1, z=2)
    */
   double axis(int n) const;

    /**
     * Get distance of point from origin
    */
   double magnitude() const;

    /**
     * Multiply the point by a double
     * 
     * @param scalar The value to multiply by
     * @return The updated point
    */
   const Point3& operator*=(double scalar);

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

/**
 * Scale a point by a scalar
 * 
 * @param p The point
 * @param s The scaling factor
 * 
 * @return The scaled point p * s
*/
Point3 operator*(const Point3& p, double s);

#endif