#include "hittable.h"

void HitRecord::setNormal(const Ray& ray, const Vector3& normal) {
    front = Dot(ray.direction(), normal) < 0.0;
    this->normal = front ? normal : -normal;
}
