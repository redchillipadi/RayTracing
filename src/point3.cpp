#include "point3.h"
#include "vector3.h"
#include <math.h>
#include "random.h"

Point3::Point3() : data{0.0, 0.0, 0.0} {}

Point3::Point3(double x, double y, double z) : data{x, y, z} {}

Point3::Point3(const Vector3& vector) : Point3(vector.x(), vector.y(), vector.z()) {}


double Point3::x() const {
    return data[0];
}

double Point3::y() const {
    return data[1];
}

double Point3::z() const {
    return data[2];
}

void Point3::setX(double value)
{
    data[0] = value;
}

void Point3::setY(double value)
{
    data[1] = value;
}

void Point3::setZ(double value)
{
    data[2] = value;
}

Point3 Point3::random() {
    return Point3::random(0.0, 1.0);
}

Point3 Point3::random(double min, double max)
{
    return Vector3(
        (max - min) * randomDouble() + min,
        (max - min) * randomDouble() + min,
        (max - min) * randomDouble() + min);
}


const Point3& Point3::operator*=(double scalar) {
    data[0] *= scalar;
    data[1] *= scalar;
    data[2] *= scalar;

    return *this;
}


double Point3::axis(int n) const {
    switch(n) {
    case 2:
        return z();

    case 1:
        return y();

    default:
        return x();
    }
}

double Point3::magnitude() const {
    return sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
}

const Point3& Point3::operator+=(const Vector3& v)
{
    data[0] += v.x();
    data[1] += v.y();
    data[2] += v.z();

    return *this;
}

Point3 operator+(const Point3& origin, const Vector3& direction) {
    return Point3(origin.x() + direction.x(), origin.y() + direction.y(), origin.z() + direction.z());
}

Point3 operator-(const Point3& origin, const Vector3& direction) {
    return Point3(origin.x() - direction.x(), origin.y() - direction.y(), origin.z() - direction.z());
}

Vector3 operator-(const Point3& p1, const Point3& p2) {
    return Vector3(p1.x() - p2.x(), p1.y() - p2.y(), p1.z() - p2.z());
}

Point3 operator*(const Point3& p, double s) {
    return Point3(p.x() * s, p.y() * s, p.z() * s);
}
