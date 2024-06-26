#include "sphere.h"
#include <math.h>

Sphere::Sphere() : initial{0, 0, 0}, radius(1), isMoving(false), velocity{0, 0, 0} {}

Sphere::Sphere(const Point3& centre, double radius, std::shared_ptr<Material> material)
 :  initial(centre),
    radius(fmax(0.0, radius)),
    material(material),
    isMoving(false),
    velocity(0, 0, 0)
{
    Vector3 vec(radius, radius, radius);
    bbox = AxisAlignedBoundingBox(centre - vec, centre + vec);
}

Sphere::Sphere(const Point3& centre1, const Point3& centre2, double radius, std::shared_ptr<Material> material)
 :  initial(centre1),
    radius(fmax(0.0, radius)),
    material(material),
    isMoving(true),
    velocity(centre2 - centre1)
{
    Vector3 vec(radius, radius, radius);
    AxisAlignedBoundingBox box1(centre1 - vec, centre1 + vec);
    AxisAlignedBoundingBox box2(centre2 - vec, centre2 + vec);
    bbox = AxisAlignedBoundingBox(box1, box2);
}

bool Sphere::Hit(const Ray& ray, Interval interval, HitRecord& hitRecord) const {
    Point3 centre = isMoving ? sphereCentre(ray.time()) : initial;
    Vector3 oc = centre - ray.origin();
    double a = ray.direction().squaredMagnitude();
    double h = Dot(ray.direction(), oc);
    double c = oc.squaredMagnitude() - radius * radius;

    double discriminant = h * h - a * c;
    if (discriminant < 0.0)
        return false;

    double sqrtDiscriminant = sqrt(discriminant);
    double root = (h - sqrtDiscriminant) / a;
    if (root <= interval.min() || root >= interval.max()) {
        root = (h + sqrtDiscriminant) / a;
        if (root <= interval.min() || root >= interval.max())
            return false;
    }

    hitRecord.t = root;
    hitRecord.point = ray.at(hitRecord.t);
    Vector3 normal = (hitRecord.point - centre) / radius;
    hitRecord.material = material;
    hitRecord.setNormal(ray, normal);

    return true;
}

AxisAlignedBoundingBox Sphere::boundingBox() const {
    return bbox;
}
