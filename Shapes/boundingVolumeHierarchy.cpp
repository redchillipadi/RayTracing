#include "boundingVolumeHierarchy.h"
#include "../random.h"
#include <iostream>
#include <algorithm>

BoundingVolumeHierarchyNode::BoundingVolumeHierarchyNode(HittableList list)
 :  BoundingVolumeHierarchyNode(list.objectVector(), 0, list.objectVector().size())
{}

BoundingVolumeHierarchyNode::BoundingVolumeHierarchyNode(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end) {
    bbox = AxisAlignedBoundingBox::empty;
    for (size_t objectIndex = start; objectIndex < end; objectIndex++)
        bbox = AxisAlignedBoundingBox(bbox, objects[objectIndex]->boundingBox());
    int axis = bbox.longestAxis();

    auto comparator = (axis == 0) ? boxCompareX : (axis==1) ? boxCompareY : boxCompareZ;

    size_t objectSpan = end - start;
    switch (objectSpan) {
    case 1:
        left = right = objects[start];
        break;

    case 2:
        left = objects[start];
        right = objects[start+1];
        break;
    
    default:
        std::sort(objects.begin() + start, objects.begin() + end, comparator);
        size_t mid = start + objectSpan/2;
        left = std::make_shared<BoundingVolumeHierarchyNode>(objects, start, mid);
        right = std::make_shared<BoundingVolumeHierarchyNode>(objects, mid, end);
        break;
    }
}

bool BoundingVolumeHierarchyNode::Hit(const Ray& ray, Interval interval, HitRecord& hitRecord) const {
    if (!bbox.hit(ray, interval))
        return false;

    bool hitLeft = left->Hit(ray, interval, hitRecord);
    bool hitRight = right->Hit(ray, Interval(interval.min(), hitLeft ? hitRecord.t : interval.max()), hitRecord);

    return hitLeft || hitRight;
};

AxisAlignedBoundingBox BoundingVolumeHierarchyNode::boundingBox() const {
    return bbox;
}; 

bool BoundingVolumeHierarchyNode::boxCompare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, int axis) {
    Interval intervalA = a->boundingBox().axisInterval(axis);
    Interval intervalB = b->boundingBox().axisInterval(axis);

    return intervalA.min() < intervalB.min();
}

bool BoundingVolumeHierarchyNode::boxCompareX(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b) {
    return boxCompare(a, b, 0);
}

bool BoundingVolumeHierarchyNode::boxCompareY(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b) {
    return boxCompare(a, b, 1);
}

bool BoundingVolumeHierarchyNode::boxCompareZ(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b) {
    return boxCompare(a, b, 2);
}
