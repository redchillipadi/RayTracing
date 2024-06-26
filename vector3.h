#ifndef VECTOR_3
#define VECTOR_3

class Point3;

/**
 * Vector class with double precision
*/
class Vector3 {
public:
    /**
     * Default constructor
     * 
     * Initialises x, y and z to 0.0
    */
    Vector3();

    /**
     * Memberwise Constructor
     * 
     * Sets x, y and z to specified values
     * 
     * @param x X distance
     * @param y Y distance
     * @param z Z distance
    */
    Vector3(double x, double y, double z);

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
     * Negate vector
     * 
     * Reverse the sign of all elements in the vector
     * 
     * @return A vector pointing in the opposite direction
    */
    Vector3 operator-() const;

    /**
     * Vector addition
     * 
     * Add one vector to another
     * 
     * @param v The vector to add
     * 
     * @return The sum of the original and new vector
    */
    Vector3& operator+=(const Vector3& v);

    /**
     * Scalar multiplication
     * 
     * Multiply the vector by a scalar
     * 
     * @param t The value to multiply by
     * 
     * @return The original vector multiplied by the scalar t
    */
   Vector3& operator*=(double t);

   /**
    * Magnitude
    * 
    * @return The length of the vector
   */
    double magnitude() const;

   /**
    * Squared Magnitude
    * 
    * @return The length of the vector
   */
    double squaredMagnitude() const;

    /**
     * Are all values in this vector close to zero?
     * 
     * @return True if the vector is near zero
    */
   bool NearZero() const;

    /**
     * Return a random vector in [0-1, 0-1, 0-1]
    */
    static Vector3 random();

    /**
     * Return a random vector in [min-max, min-max, min-max]
    */
    static Vector3 random(double min, double max);

private:
    double data[3];
};

/**
 * Multiply a scalar by a vector
 * 
 * @param t The scalar to multiply by
 * @param v The vector to multiply
 * 
 * @return The multiplied vector
*/
Vector3 operator*(double t, const Vector3& v);

/**
 * Multiply a vector by a scalar
 * 
 * @param v The vector to multiply
 * @param t The scalar to multiply by
 * 
 * @return The scaled vector
*/
Vector3 operator*(const Vector3& v, double t);

/**
 * Divide a vector by a scalar
 * 
 * @param v The vector to divide
 * @param t The scalar to divide by
 * 
 * @return The scaled vector
*/
Vector3 operator/(const Vector3& v, double t);

/**
 * Add a vector and a point
 * 
 * @param direction The direction vector to add
 * @param origin The point of origin
 * 
 * @return The new point at v + p
*/
Point3 operator+(const Vector3& direction, const Point3& origin);

/**
 * Add two vectors
 * 
 * @param v1 The first vector
 * @param v2 The second vector
 * 
 * @return The new vector v1 + v2
*/
Vector3 operator+(const Vector3& v1, const Vector3& v2);

/**
 * Subtract one vector from another
 * 
 * @param v1 The first vector
 * @param v2 The second vector
 * 
 * @return The new vector v1 - v2
*/
Vector3 operator-(const Vector3& v1, const Vector3& v2);

/**
 * Normalises the vector to unit length
 *
 * @param v The vector to normalise
 * 
 * @return The normalised vector v of unit length
*/
Vector3 Normalise(const Vector3& v);

/**
 * Return the dot product of two vectors
 * 
 * @param v1 The first vector
 * @param v2 The second vector
 * 
 * @return The dot product
*/
double Dot(const Vector3& v1, const Vector3& v2);

/**
 * Return th cross product of two vectors
 * 
 * @param v1 The first vector
 * @param v2 The second vector
 * 
 * @return The cross product
*/
Vector3 Cross(const Vector3& v1, const Vector3& v2);

/**
 * Random in unit sphere
 * 
 * @return A vrandomly selected vector within the unit sphere
*/
Vector3 randomInUnitSphere();

/**
 * Random unit vector
 * 
 * @return A random unit vector
*/
Vector3 randomUnitVector();

/**
 * Random in unit disk
 * 
 * @return A random vector within a disk around the origin in XY plane
*/
Vector3 randomInUnitDisk();

/**
 * Random vector on hemisphere
 * 
 * @param normal The surface normal, pointing towards the apex of the hemisphere
 * 
 * @return A random vector in the hemisphere with apex at the normal
*/
Vector3 randomOnHemisphere(const Vector3& normal);

/**
 * Reflect a vector at the intersection point
 * 
 * @param intersection Vector containing the point of intersection with the surface
 * @param normal Vector containing the surface normal
 * 
 * @return The reflected vector
*/
Vector3 reflect(const Vector3& intersection, const Vector3& normal);

/**
 * Determine refraction as the beam passes between materials with different refractive indices
 * 
 * @param incident Incident vector
 * @param normal Normal to the surface
 * @param refractiveIndexRatio Ratio of eta to eta' (Incoming vs outgoing refractive indices of the materials)
 * 
 * @return The refracted vector
*/
Vector3 refract(const Vector3& incident, const Vector3& normal, double refractiveIndexRatio);


#endif