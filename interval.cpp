#include "interval.h"

Interval::Interval() : a(+infinity), b(-infinity) {}

Interval::Interval(double min, double max) : a(min), b(max) {}

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

double Interval::min() const {
    return a;
}

double Interval::max() const {
    return b;
}

double Interval::size() const {
    return b - a;
}

bool Interval::contains(double x) const {
    return a <= x && x <= b;
}

bool Interval::surrounds(double x) const {
    return a < x && x < b;
}

double Interval::clamp(double x) const {
    if (x <= a) return a;
    if (x >= b) return b;
    return x;
}

Interval Interval::expand(double delta) const {
    double padding = delta / 2.0;
    return Interval(a - padding, b + padding);
}
