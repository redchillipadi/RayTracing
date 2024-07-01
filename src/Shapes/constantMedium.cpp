#include "constantMedium.h"
#include "../Materials/isotropic.h"
#include "../random.h"
#include <iostream>

ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> boundary, double density, std::shared_ptr<Texture> texture)
 :  boundary(boundary),
    negInvDensity(-1.0 / density),
    phaseFunction(std::make_shared<Isotropic>(texture))
{}

ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> boundary, double density, const Colour& albedo)
 :  boundary(boundary),
    negInvDensity(-1.0 / density),
    phaseFunction(std::make_shared<Isotropic>(albedo))
{}

bool ConstantMedium::Hit(const Ray& ray, Interval interval, HitRecord& hitRecord) const
{
    const bool enableDebug = false;
    const bool debugging = enableDebug && randomDouble() < 0.00001;

    HitRecord rec1, rec2;

    if (!boundary->Hit(ray, Interval::universe, rec1))
        return false;

    if (!boundary->Hit(ray, Interval(rec1.t+0.0001, infinity), rec2))
        return false;

    if (debugging)
        std::clog << "\nt_min=" << rec1.t << ", t_max=" << rec2.t << "\n";

    if (rec1.t < interval.min())
        rec1.t = interval.min();
    if (rec2.t > interval.max())
        rec2.t = interval.max();

    if (rec1.t >= rec2.t)
        return false;

    if (rec1.t < 0.0)
        return false;

    double rayLength = ray.direction().magnitude();
    double distanceInsideBoundary = (rec2.t - rec1.t) * rayLength;
    double hitDistance = negInvDensity * log(randomDouble());

    if (hitDistance > distanceInsideBoundary)
        return false;

    hitRecord.t = rec1.t + hitDistance / rayLength;
    hitRecord.point = ray.at(hitRecord.t);

    if (debugging)
        std::clog << "hit_distance = " << hitDistance << "\n"
            << "rec.t = " << hitRecord.t << "\n"
            << "rec.point = " << hitRecord.point.x() << ", " << hitRecord.point.y() << ", " << hitRecord.point.z() << std::endl;

    hitRecord.normal = Vector3(1, 0, 0);
    hitRecord.front = true;
    hitRecord.material = phaseFunction;

    return true;    
}

AxisAlignedBoundingBox ConstantMedium::boundingBox() const
{
    return boundary->boundingBox();
}
