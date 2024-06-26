main: main.cpp main.h vector3.cpp vector3.h colour.cpp colour.h ray.cpp ray.h point3.h point3.cpp interval.h interval.cpp camera.h camera.cpp \
		random.h random.cpp \
		Shapes/hittable.h Shapes/hittable.cpp Shapes/sphere.h Shapes/sphere.cpp Shapes/hittableList.h Shapes/hittableList.cpp \
		Shapes/axisAlignedboundingBox.h Shapes/axisAlignedboundingBox.cpp Shapes/boundingVolumeHierarchy.h Shapes/boundingVolumeHierarchy.cpp \
		Materials/material.h Materials/material.cpp Materials/lambertian.h Materials/lambertian.cpp Materials/metal.h Materials/metal.cpp \
		Materials/dielectric.h Materials/dielectric.cpp
	g++ --std=c++20 -o main main.cpp vector3.cpp colour.cpp ray.cpp point3.cpp interval.cpp camera.cpp random.cpp \
		Shapes/hittable.cpp Shapes/sphere.cpp Shapes/hittableList.cpp Shapes/axisAlignedboundingBox.cpp Shapes/boundingVolumeHierarchy.cpp \
		Materials/material.cpp Materials/lambertian.cpp Materials/metal.cpp Materials/dielectric.cpp \
		-I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system