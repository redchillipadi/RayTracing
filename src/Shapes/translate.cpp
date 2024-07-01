#include "translate.h"

Translate::Translate(std::shared_ptr<Hittable> object, const Vector3& offset)
  : object(object), offset(offset)
{
    bbox = object->boundingBox() + offset;
}

bool Translate::Hit(const Ray& ray, Interval interval, HitRecord& hitRecord) const
{
    Ray offsetRay{ray.origin() - offset, ray.direction(), ray.time()};

    if (!object->Hit(offsetRay, interval, hitRecord))
        return false;


    hitRecord.point += offset;

    return true;
}

AxisAlignedBoundingBox Translate::boundingBox() const
{
    return bbox;
}

