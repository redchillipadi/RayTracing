cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
target_sources(RayTracing PRIVATE axisAlignedBoundingBox.cpp boundingVolumeHierarchy.cpp hittable.cpp hittableList.cpp sphere.cpp quad.cpp)