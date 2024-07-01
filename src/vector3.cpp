#include "vector3.h"
#include "point3.h"
#include <math.h>
#include "random.h"

Vector3::Vector3() : data{0.0, 0.0, 0.0} {}

Vector3::Vector3(double x, double y, double z) : data{x, y, z} {}

Vector3::Vector3(const Point3& point) : data{point.x(), point.y(), point.z()} {}

double Vector3::x() const {
    return data[0];
}

double Vector3::y() const {
    return data[1];
}

double Vector3::z() const {
    return data[2];
}

double Vector3::axis(int n) const {
    switch(n) {
    case 2:
        return z();

    case 1:
        return y();

    default:
        return x();
    }
}


Vector3 Vector3::operator-() const {
    return Vector3(-data[0], -data[1], -data[2]);
}


Vector3& Vector3::operator+=(const Vector3& v) {
    data[0] += v.data[0];
    data[1] += v.data[1];
    data[2] += v.data[2];
    return *this;
}

Vector3& Vector3::operator*=(double t) {
    data[0] *= t;
    data[1] *= t;
    data[2] *= t;
    return *this;
}

double Vector3::magnitude() const {
    return sqrt(this->squaredMagnitude());
}

double Vector3::squaredMagnitude() const {
    return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
}

bool Vector3::NearZero() const {
    const double threshold = 1e-8;
    return (fabs(data[0]) < threshold) && (fabs(data[1]) < threshold) && (fabs(data[2]) < threshold);
}

Vector3 Vector3::random() {
    return Vector3::random(0.0, 1.0);
}

Vector3 Vector3::random(double min, double max) {
    return Vector3(
        (max - min) * randomDouble() + min,
        (max - min) * randomDouble() + min,
        (max - min) * randomDouble() + min);
}

Vector3 operator*(double t, const Vector3& v) {
    return Vector3(t * v.x(), t * v.y(), t * v.z());
}

Vector3 operator*(const Vector3& v, double t) {
    return t * v;
}

Vector3 operator/(const Vector3& v, double t) {
    return v * (1.0 / t);
}


Point3 operator+(const Vector3& direction, const Point3& origin) {
    return origin + direction;
}

Vector3 operator+(const Vector3& v1, const Vector3& v2) {
    return Vector3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

Vector3 operator-(const Vector3& v1, const Vector3& v2) {
    return Vector3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}


Vector3 Normalise(const Vector3& v) {
    return v / v.magnitude();
}

double Dot(const Vector3& v1, const Vector3& v2) {
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
    return Vector3(
        v1.y() * v2.z() - v1.z() * v2.y(),
        v1.z() * v2.x() - v1.x() * v2.z(),
        v1.x() * v2.y() - v1.y() * v2.x());
}


Vector3 randomInUnitSphere() {
    while (true) {
        Vector3 point = Vector3::random(-1.0, 1.0);
        if (point.squaredMagnitude() < 1.0)
            return point;
    }
}

Vector3 randomInUnitDisk() {
    while (true) {
        Vector3 point = Vector3(randomDouble(-1.0, 1.0), randomDouble(-1.0, 1.0), 0.0);
        if (point.squaredMagnitude() < 1.0)
            return point;
    }
}


Vector3 randomUnitVector() {
    return Normalise(randomInUnitSphere());
}

Vector3 randomOnHemisphere(const Vector3& normal) {
    Vector3 unit = randomUnitVector();
    return (Dot(unit, normal) > 0.0) ? unit : -unit;
}

Vector3 reflect(const Vector3& intersection, const Vector3& normal)
{
    return intersection - 2.0 * Dot(intersection, normal) * normal;
}

Vector3 refract(const Vector3& incident, const Vector3& normal, double refractiveIndexRatio)
{
    double cosTheta = fmin(Dot(-incident, normal), 1.0);
    Vector3 rayOutPerpendicular = refractiveIndexRatio * (incident + cosTheta * normal);
    Vector3 rayOutParallel = -sqrt(fabs(1.0 - rayOutPerpendicular.squaredMagnitude())) * normal;
    return rayOutPerpendicular + rayOutParallel;
}
