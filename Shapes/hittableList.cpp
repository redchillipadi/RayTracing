#include "hittableList.h"

HittableList::HittableList() {}

HittableList::HittableList(std::shared_ptr<Hittable> object)
{
    add(object);
    bbox = AxisAlignedBoundingBox(bbox, object->boundingBox());
}

void HittableList::clear()
{
    objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> object)
{
    objects.push_back(object);
}

bool HittableList::Hit(const Ray& ray, Interval interval, HitRecord& hitRecord) const {
    HitRecord record;
    bool collision = false;
    double shortestDistance = interval.max();

    for (const auto& object : objects) {
        if (object->Hit(ray, Interval(interval.min(), shortestDistance), record)) {
            collision = true;
            shortestDistance = record.t;
            hitRecord = record;
        }
    }

    return collision;
}

AxisAlignedBoundingBox HittableList::boundingBox() const {
    return bbox;
}
