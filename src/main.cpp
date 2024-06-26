#include "main.h"
#include "camera.h"
#include "point3.h"
#include "ray.h"
#include "vector3.h"
#include "Shapes/hittable.h"
#include "Shapes/hittableList.h"
#include "Shapes/sphere.h"
#include "Shapes/boundingVolumeHierarchy.h"
#include "Materials/material.h"
#include "Materials/lambertian.h"
#include "Materials/metal.h"
#include "Materials/dielectric.h"
#include "random.h"
#include <iostream>
#include <memory>

int main()
{
    // Test DOF
    int width = 400;
    int height = 225;

    Camera camera(width, height, 100, 50);
    HittableList world;

    std::shared_ptr<Lambertian> materialGround = std::make_shared<Lambertian>(Colour(0.8, 0.8, 0.0));
    std::shared_ptr<Lambertian> materialCentre = std::make_shared<Lambertian>(Colour(0.1, 0.2, 0.5));
    std::shared_ptr<Dielectric> materialLeft = std::make_shared<Dielectric>(1.5);
    std::shared_ptr<Dielectric> materialBubble = std::make_shared<Dielectric>(1.0 / 1.5);
    std::shared_ptr<Metal> materialRight = std::make_shared<Metal>(Colour(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100, materialGround));
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, materialCentre));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.4, materialBubble));
    world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight));

    camera.setVFOV(20);
    camera.setOrientation(Point3(-2,2,1), Point3(0, 0, -1), Vector3(0, 1, 0));
    camera.setAperture(1.0, 3.4);
    
    /*
    // Final Scene
    int width = 400;
    int height = 225;

    Camera camera(width, height, 100, 50);
    HittableList world;

    camera.setVFOV(20);
    camera.setOrientation(Point3(13,2,3), Point3(0, 0, 0), Vector3(0, 1, 0));
    camera.setAperture(0.6, 10.0);

    std::shared_ptr<Lambertian> materialGround = std::make_shared<Lambertian>(Colour(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Point3(0.0, -1000.0, 0.0), 1000.0, materialGround));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double chooseMat = randomDouble();
            Point3 centre(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((centre - Point3(4, 0.2, 0)).magnitude() > 0.9) {
                std::shared_ptr<Material> sphereMaterial;

                if (chooseMat < 0.8) {
                    Colour albedo = Colour::random() * Colour::random();
                    sphereMaterial = std::make_shared<Lambertian>(albedo);
                    Point3 centre2  = centre + Vector3(0, randomDouble(0, 0.5), 0);
                    world.add(std::make_shared<Sphere>(centre, centre2, 0.2, sphereMaterial));
                } else if (chooseMat < 0.95) {
                    Colour albedo = Colour::random(0.5, 1);
                    double fuzz = randomDouble(0, 0.5);
                    sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(centre, 0.2, sphereMaterial));
                } else {
                    sphereMaterial = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(centre, 0.2, sphereMaterial));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Colour(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Colour(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));
    */

    //world = HittableList(std::make_shared<BoundingVolumeHierarchyNode>(world));

    sf::RenderWindow window(sf::VideoMode(width, height), "My Window");
    sf::Uint8* pixels = new sf::Uint8[width * height * 4];
    if (pixels == nullptr) {
        std::cerr << "Unable to allocate pixel buffer" << std::endl;
        return 0;
    }

    sf::Texture texture;
    if (!texture.create(width, height)) {
        std::cerr << "Unable to create texture" << std::endl;
        return 0;
    }

    sf::Sprite sprite;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        camera.render(world, pixels);
        texture.update(pixels);
        sprite.setTexture(texture);
        window.draw(sprite);

        window.display();
    }

    return 0;
}