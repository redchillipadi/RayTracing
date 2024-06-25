#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

/**
 * A class dealing with a scalar interval
*/
class Interval {
public:
    /**
     * Default constructor
     * 
     * Create an empty interval
    */
    Interval();

    /**
     * Memberwise constructor
     * 
     * Create an interval between min and max
     * 
     * @param min The minimum permissible value
     * @param max The maximum permissible value
    */
    Interval(double min, double max);

    /**
     * Get the minimum value
     * 
     * @return The minimum value of the interval
    */
    double min() const;

    /**
     * Get the maximum value
     * 
     * @return The maximum value of the interval
    */
    double max() const;

    /**
     * Return the size contained within the interval
     * 
     * @return The size of the interval
    */
    double size() const;

    /**
     * Expand an interval by a given amount
     * 
     * @param delta The amount of padding to add
     * @return the expanded interval
    */
    Interval expand(double delta) const;

    /**
     * Test whether x is within the range [min, max]
     * 
     * @return true if the interval contains x
    */
    bool contains(double x) const;

    /**
     * Test whether x is within the range (min, max)
     * 
     * @return true if the interval surrounds x
    */
    bool surrounds(double x) const;

    /**
     * Clamp the value of x to be within the interval
     * 
     * @return The value of x clamped to remain within the interval
    */
    double clamp(double x) const;

    /**
     * The empty interval contains nothibng
    */
    static const Interval empty;

    /**
     * The universe interval stretches to infinity in both directions
    */
    static const Interval universe;

private:
    double a;
    double b;
};

/**
 * Approximate infinity with the largest possible double value
*/
const double infinity = std::numeric_limits<double>::infinity();

#endif