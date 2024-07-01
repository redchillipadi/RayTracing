#include "rotateY.h"
#include "../convert.h"

RotateY::RotateY(std::shared_ptr<Hittable> object, double angle)
  : object(object)
{
    double radians = degreesToRadians(angle);
    sinTheta = sin(radians);
    cosTheta = cos(radians);
    bbox = object->boundingBox();

    Point3 min(infinity, infinity, infinity);
    Point3 max(-infinity, -infinity, -infinity);

    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            for (int k=0; k<2; k++) {
                double x = i * bbox.axisInterval(0).max() + (1-i) * bbox.axisInterval(0).min();
                double y = j * bbox.axisInterval(1).max() + (1-j) * bbox.axisInterval(1).min();
                double z = k * bbox.axisInterval(2).max() + (1-k) * bbox.axisInterval(2).min();

                double newX = cosTheta * x + sinTheta * y;
                double newZ = -sinTheta * x + cosTheta * z;

                Vector3 tester(newX, y, newZ);

                min.setX(fmin(min.x(), tester.x()));
                min.setY(fmin(min.y(), tester.y()));
                min.setZ(fmin(min.z(), tester.z()));
                max.setX(fmax(max.x(), tester.x()));
                max.setY(fmax(max.y(), tester.y()));
                max.setZ(fmax(max.z(), tester.z()));
            }
        }
    }
    bbox = AxisAlignedBoundingBox(min, max);
}

bool RotateY::Hit(const Ray& ray, Interval interval, HitRecord& hitRecord) const
{
    Point3 origin{ray.origin()};
    Vector3 direction{ray.direction()};

    origin.setX(cosTheta * ray.origin().axis(0) - sinTheta * ray.origin().axis(2));
    origin.setZ(sinTheta * ray.origin().axis(0) + cosTheta * ray.origin().axis(2));

    direction.setX(cosTheta * ray.direction().axis(0) - sinTheta * ray.direction().axis(2));
    direction.setZ(sinTheta * ray.direction().axis(0) + cosTheta * ray.direction().axis(2));

    Ray rotatedRay{origin, direction, ray.time()};

    if (!object->Hit(rotatedRay, interval, hitRecord))
        return false;

    Point3 point = hitRecord.point;
    point.setX(cosTheta * hitRecord.point.axis(0) + sinTheta * hitRecord.point.axis(2));
    point.setZ(-sinTheta * hitRecord.point.axis(0) + cosTheta * hitRecord.point.axis(2));

    Vector3 normal{hitRecord.normal};
    normal.setX(cosTheta * hitRecord.normal.axis(0) + sinTheta * hitRecord.normal.axis(2));
    normal.setZ(-sinTheta * hitRecord.normal.axis(0) + cosTheta * hitRecord.normal.axis(2));

    hitRecord.point = point;
    hitRecord.normal = normal;

    return true;
}

AxisAlignedBoundingBox RotateY::boundingBox() const
{
    return bbox;
}



