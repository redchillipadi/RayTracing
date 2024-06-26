#include "interval.h"

Interval::Interval() : a(+infinity), b(-infinity) {}

Interval::Interval(double min, double max) : a(min), b(max) {}

Interval::Interval(const Interval& int1, const Interval& int2) {
    a = int1.min() <= int2.min() ? int1.min() : int2.min();
    b = int1.max() <= int2.max() ? int1.max() : int2.max();
}

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

double Interval::min() const {
    return a;
}

double Interval::max() const {
    return b;
}

void Interval::setMin(double min) {
    a = min;
}

void Interval::setMax(double max) {
    b = max;
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
