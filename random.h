#ifndef RANDOM_H
#define RANDOM_H

/**
 * Return a random double in the range [0, 1)
*/
double randomDouble();

/**
 * Return a random double in the range [min, max)
 *
 * @param min The minimum value to return
 * @param max The maximum value to return
*/
double randomDouble(double min, double max);

/**
 * Return a random int in the range [min, max]
 * 
 * @param min The minimum value to return
 * @param max The maximum value to return
*/
int randomInt(int min, int max);

#endif