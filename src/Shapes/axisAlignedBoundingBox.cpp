#include "axisAlignedBoundingBox.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox() {}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Interval& x, const Interval& y, const Interval& z) 
 :  x(x),
    y(y),
    z(z)
{
    padToMinimums();
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2) {
    x = Interval(aabb1.x, aabb2.x);
    y = Interval(aabb1.y, aabb2.y);
    z = Interval(aabb1.z, aabb2.z);

    padToMinimums();
}


AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Point3& p1, const Point3& p2) {
    x = (p1.x() <= p2.x()) ? Interval(p1.x(), p2.x()) : Interval(p2.x(), p1.x());
    y = (p1.y() <= p2.y()) ? Interval(p1.y(), p2.y()) : Interval(p2.y(), p1.y());
    z = (p1.z() <= p2.z()) ? Interval(p1.z(), p2.z()) : Interval(p2.z(), p1.z());

    padToMinimums();
}

const Interval& AxisAlignedBoundingBox::axisInterval(int n) const {
    switch (n) {
    case 2:
        return z;

    case 1:
        return y;

    default:
        return x;
    }
}

bool AxisAlignedBoundingBox::hit(const Ray& ray, Interval interval) const {
    const Point3& rayOrigin = ray.origin();
    const Vector3& rayDirection = ray.direction();

    for (int axis=0; axis<3; axis++) {
        const Interval& ax = axisInterval(axis);
        const double adInv = 1.0 / rayDirection.axis(axis);

        double t0 = (ax.min() - rayOrigin.axis(axis)) * adInv;
        double t1 = (ax.max() - rayOrigin.axis(axis)) * adInv;

        if (t0 < t1) {
            if (t0 > interval.min()) interval.setMin(t0);
            if (t1 < interval.max()) interval.setMax(t1);
        } else {
            if (t1 > interval.min()) interval.setMin(t1);
            if (t0 < interval.max()) interval.setMax(t0);
        }

        if (interval.max() <= interval.min())
            return false;
    }

    return true;
}

int AxisAlignedBoundingBox::longestAxis() const {
    return (x.size() > y.size()) ? ((x.size() > z.size()) ? 0 : 2) : ((y.size() > z.size()) ? 1 : 2);
}


const AxisAlignedBoundingBox AxisAlignedBoundingBox::empty = AxisAlignedBoundingBox(Interval::empty, Interval::empty, Interval::empty);
const AxisAlignedBoundingBox AxisAlignedBoundingBox::universe = AxisAlignedBoundingBox(Interval::universe, Interval::universe, Interval::universe);

void AxisAlignedBoundingBox::padToMinimums() {
    double delta = 0.0001;
    if (x.size() < delta) x = x.expand(delta);
    if (y.size() < delta) y = y.expand(delta);
    if (z.size() < delta) z = z.expand(delta);
}


AxisAlignedBoundingBox operator+(const AxisAlignedBoundingBox& aabb, const Vector3& v)
{
    return AxisAlignedBoundingBox(aabb.axisInterval(0) + v.x(), aabb.axisInterval(1) + v.y(), aabb.axisInterval(2) + v.z());
}
