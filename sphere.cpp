#include "sphere.h"
#include <math.h>

Sphere::Sphere() : centre{0, 0, 0}, radius(1) {}

Sphere::Sphere(const Point3& centre, double radius, std::shared_ptr<Material> material)
 :  centre(centre),
    radius(fmax(0.0, radius)),
    material(material)
{}

bool Sphere::Hit(const Ray& ray, Interval interval, HitRecord& hitRecord) const {
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

void Sphere::move(const Vector3& displacement) {
    centre = centre + displacement;
}
