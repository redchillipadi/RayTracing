#ifndef COLOUR_H
#define COLOUR_H

class Vector3;

/**
 * A class to store colours in RGB format
 * 
 * The values for each channel are doubles in the range [0, 1]
*/
class Colour {
public:
    /**
     * Default constructor
     * 
     * Initialises r, g and b to 0.0 (black)
    */
    Colour();

    /**
     * Memberwise Constructor
     * 
     * Sets r, g and b to specified values
     * 
     * @param r Red channel (0 - 1)
     * @param g Green channel (0 - 1)
     * @param b Blue channel (0 - 1)
    */
    Colour(double r, double g, double b);

    /**
     * Get red channel
     * 
     * @return red channel (0 - 1)
    */
    double r() const;

    /**
     * Get green channel
     * 
     * @return green channel (0 - 1)
    */
    double g() const;

    /**
     * Get blue channel
     * 
     * @return Zblue channel (0 - 1)
    */
    double b() const;

    /**
    * Add another colour to this one
    * 
    * @param c The colour to add
    * 
    * @returns the new colour
    */
    Colour& operator+=(const Colour& c);

    /**
     * Return a random colour
     * 
     * @returns a randomly selected colour
    */
   static Colour random();

    /**
     * Return a random colour
     * 
     * @param min Minimum value for each channel
     * @param max Maximum value for each channel
     * 
     * @returns a randomly selected colour
    */
   static Colour random(double min, double max);


private:
    double data[3];
};

/**
 * Multiply a scalar by a colour
 * 
 * @param a The scalar to multiply by
 * @param c The colour to multiply
 * 
 * @return The multiplied colour
*/
Colour operator*(double a, const Colour& c);

/**
 * Multiply two colours together
 * 
 * @param c1 The first colour
 * @param c2 The second colour
 * 
 * @returns the new colour c1 * c2
*/
Colour operator*(const Colour& c1, const Colour& c2);


/**
 * Add two colours together
 * 
 * @param c1 The first colour
 * @param c2 The second colour
 * 
 * @returns the new colour c1 + c2
*/
Colour operator+(const Colour& c1, const Colour& c2);

/**
 * Add a vector and a colour together
 * 
 * @param v The vector (to treat XYZ as RGB)
 * @param c The colour
 * 
 * @returns the new colour v + c
*/
Colour operator+(const Vector3& v, const Colour& c);

#endif