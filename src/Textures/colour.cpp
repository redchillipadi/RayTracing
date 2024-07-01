#include "colour.h"
#include "../vector3.h"
#include "../random.h"

Colour::Colour() : data{0.0, 0.0, 0.0} {}

Colour::Colour(double r, double g, double b)
  : data{r, g, b} {}

double Colour::r() const {
    return data[0];
}

double Colour::g() const {
    return data[1];
}

double Colour::b() const {
    return data[2];
}

Colour& Colour::operator+=(const Colour& c) {
    data[0] += c.r();
    data[1] += c.g();
    data[2] += c.b();
    return *this;
}

Colour Colour::random() {
    return Colour(
        randomDouble(),
        randomDouble(),
        randomDouble()
    );
}

Colour Colour::random(double min, double max) {
    return Colour(
        randomDouble(min, max),
        randomDouble(min, max),
        randomDouble(min, max)
    );
}


Colour operator*(double a, const Colour& c) {
    return Colour(a * c.r(), a * c.g(), a * c.b());
}

Colour operator*(const Colour& c1, const Colour& c2) {
    return Colour(c1.r() * c2.r(), c1.g() * c2.g(), c1.b() * c2.b());
}


Colour operator+(const Colour& c1, const Colour& c2) {
    return Colour(c1.r() + c2.r(), c1.g() + c2.g(), c1.b() + c2.b());
}

Colour operator+(const Vector3& v, const Colour& c) {
    return Colour(v.x() + c.r(), v.y() + c.g(), v.z() + c.b());
}

Colour operator*(const Colour& c, double s) {
    return Colour(c.r() * s, c.g() * s, c.b() * s);
}
