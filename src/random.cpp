#include "random.h"
#include <random>

double randomDouble()
{
    return randomDouble(0.0, 1.0);
};

double randomDouble(double min, double max)
{
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);

    return (max - min) * distribution(generator) + min;
}

int randomInt(int min, int max)
{
    return int(randomDouble(min, max+1));
}
