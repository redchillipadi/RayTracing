#include "quad.h"

Quad::Quad(const Point3& origin, const Vector3& u, const Vector3& v, std::shared_ptr<Material> material)
    : origin_(origin), u_(u), v_(v), material_(material)
{
    Vector3 n = Cross(u, v);
    normal_ = Normalise(n);
    D_ = Dot(normal_, origin);
    w_ = n / Dot(n, n);

    setBoundingBox();
}

void Quad::setBoundingBox()
{
    auto bbox_diagonal1 = AxisAlignedBoundingBox(origin_, origin_ + u_ + v_);
    auto bbox_diagonal2 = AxisAlignedBoundingBox(origin_ + u_, origin_ + v_);
    bbox_ = AxisAlignedBoundingBox(bbox_diagonal1, bbox_diagonal2);
}

AxisAlignedBoundingBox Quad::boundingBox() const {
    return bbox_;
}

bool Quad::Hit(const Ray& ray, Interval interval, HitRecord& hitRecord) const {
    double denominator = Dot(normal_, ray.direction());

    if (fabs(denominator) < 1e-8)
        return false;

    double t = (D_ - Dot(normal_, ray.origin())) / denominator;
    if (!interval.contains(t))
        return false;

    Point3 intersection = ray.at(t);
    Vector3 planarHitPointVector = intersection - origin_;
    double alpha = Dot(w_, Cross(planarHitPointVector, v_));
    double beta = Dot(w_, Cross(u_, planarHitPointVector));

    if (!isInterior(alpha, beta, hitRecord))
        return false;

    hitRecord.t = t;
    hitRecord.point = intersection;
    hitRecord.material = material_;
    hitRecord.setNormal(ray, normal_);

    return true;
}

bool Quad::isInterior(double alpha, double beta, HitRecord& hitRecord) const
{
    Interval unitInterval{0, 1};

    if (!unitInterval.contains(alpha) || !unitInterval.contains(beta))
        return false;

    hitRecord.u = alpha;
    hitRecord.v = beta;

    return true;
}
