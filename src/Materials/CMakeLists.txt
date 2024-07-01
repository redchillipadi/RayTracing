cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
target_sources(RayTracing PRIVATE dielectric.cpp lambertian.cpp material.cpp metal.cpp diffuseLight.cpp isotropic.cpp)