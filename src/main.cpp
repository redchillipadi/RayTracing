#include "main.h"

void renderScene(int width, int height, Camera& camera, const HittableList& world) {
    sf::RenderWindow window(sf::VideoMode(width, height), "My Window");
    sf::Uint8* pixels = new sf::Uint8[width * height * 4];
    if (pixels == nullptr) {
        std::cerr << "Unable to allocate pixel buffer" << std::endl;
        return;
    }

    sf::Texture texture;
    if (!texture.create(width, height)) {
        std::cerr << "Unable to create texture" << std::endl;
        return;
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

        window.clear(sf::Color::Black);
        sprite.setTexture(texture);
        window.draw(sprite);

        window.display();
    }
}

void sceneDepthOfField() {
    int width = 400;
    int height = 225;

    Camera camera(width, height, 100, 50);
    camera.setVFOV(20);
    camera.setOrientation(Point3(-2,2,1), Point3(0, 0, -1), Vector3(0, 1, 0));
    camera.setAperture(1.0, 3.4);
    camera.setBackground(Colour(0.7, 0.8, 1.0));

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


    world = HittableList(std::make_shared<BoundingVolumeHierarchyNode>(world));

    renderScene(width, height, camera, world);
}

void sceneBouncingSpheres() {
    int width = 400;
    int height = 225;

    Camera camera(width, height, 100, 50);
    HittableList world;

    camera.setVFOV(20);
    camera.setOrientation(Point3(13,2,3), Point3(0, 0, 0), Vector3(0, 1, 0));
    camera.setAperture(0, 10.0);
    camera.setBackground(Colour(0.7, 0.8, 1.0));

    std::shared_ptr<CheckerTexture> checker = std::make_shared<CheckerTexture>(0.32, Colour(0.2, 0.3, 0.1), Colour(0.9, 0.9, 0.9));
    std::shared_ptr<Lambertian> materialGround = std::make_shared<Lambertian>(checker);
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

    world = HittableList(std::make_shared<BoundingVolumeHierarchyNode>(world));

    renderScene(width, height, camera, world);
}

void sceneCheckeredSpheres() {
    int width = 400;
    int height = 225;

    Camera camera(width, height, 100, 50);
    HittableList world;

    camera.setVFOV(20);
    camera.setOrientation(Point3(13,2,3), Point3(0, 0, 0), Vector3(0, 1, 0));
    camera.setAperture(0, 10.0);
    camera.setBackground(Colour(0.7, 0.8, 1.0));

    std::shared_ptr<CheckerTexture> checker = std::make_shared<CheckerTexture>(0.32, Colour(0.2, 0.3, 0.1), Colour(0.9, 0.9, 0.9));
    world.add(std::make_shared<Sphere>(Point3(0, -10, 0), 10, std::make_shared<Lambertian>(checker)));
    world.add(std::make_shared<Sphere>(Point3(0, 10, 0), 10, std::make_shared<Lambertian>(checker)));

    renderScene(width, height, camera, world);
}

void sceneEarth() {
    int width = 400;
    int height = 225;

    Camera camera(width, height, 100, 50);
    camera.setVFOV(20);
    camera.setOrientation(Point3(0, 0, 12), Point3(0, 0, 0), Vector3(0, 1, 0));
    camera.setAperture(0.0, 10.0);
    camera.setBackground(Colour(0.7, 0.8, 1.0));

    HittableList world;
    std::shared_ptr<ImageTexture> earthTexture = std::make_shared<ImageTexture>("earthmap.jpg");
    std::shared_ptr<Lambertian> earthSurface = std::make_shared<Lambertian>(earthTexture);
    std::shared_ptr<Sphere> globe = std::make_shared<Sphere>(Point3(0, 0, 0), 2, earthSurface);

    world.add(globe);

    renderScene(width, height, camera, world);
}

void perlinSpheres() {
    int width = 400;
    int height = 225;

    Camera camera(width, height, 100, 50);
    camera.setVFOV(20);
    camera.setOrientation(Point3(13, 2, 3), Point3(0, 0, 0), Vector3(0, 1, 0));
    camera.setAperture(0.0, 10.0);
    camera.setBackground(Colour(0.7, 0.8, 1.0));

    HittableList world;
    std::shared_ptr<NoiseTexture> texture = std::make_shared<NoiseTexture>(4);
    world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, std::make_shared<Lambertian>(texture)));
    world.add(std::make_shared<Sphere>(Point3(0, 2, 0), 2, std::make_shared<Lambertian>(texture)));

    renderScene(width, height, camera, world);
}

void quads() {
    int width = 400;
    int height = 400;

    Camera camera(width, height, 100, 50);
    camera.setVFOV(80);
    camera.setOrientation(Point3(0, 0, 9), Point3(0, 0, 0), Vector3(0, 1, 0));
    camera.setAperture(0.0, 10.0);
    camera.setBackground(Colour(0.7, 0.8, 1.0));

    HittableList world;

    std::shared_ptr<Material> leftRed = std::make_shared<Lambertian>(Colour(1.0, 0.2, 0.2));
    std::shared_ptr<Material> backGreen = std::make_shared<Lambertian>(Colour(0.2, 1.0, 0.2));
    std::shared_ptr<Material> rightBlue = std::make_shared<Lambertian>(Colour(0.2, 0.2, 1.0));
    std::shared_ptr<Material> upperOrange = std::make_shared<Lambertian>(Colour(1.0, 0.5, 0.0));
    std::shared_ptr<Material> lowerTeal = std::make_shared<Lambertian>(Colour(0.2, 0.8, 0.8));

    world.add(std::make_shared<Quad>(Point3(-3, -2, 5), Vector3(0, 0, -4), Vector3(0, 4, 0), leftRed));
    world.add(std::make_shared<Quad>(Point3(-2, -2, 0), Vector3(4, 0, 0), Vector3(0, 4, 0), backGreen));
    world.add(std::make_shared<Quad>(Point3(3, -2, 1), Vector3(0, 0, 4), Vector3(0, 4, 0), rightBlue));
    world.add(std::make_shared<Quad>(Point3(-2, 3, 1), Vector3(4, 0, 0), Vector3(0, 0, 4), upperOrange));
    world.add(std::make_shared<Quad>(Point3(-2, -3, 5), Vector3(4, 0, 0), Vector3(0, 0, -4), lowerTeal));

    renderScene(width, height, camera, world);    
}

void simpleLights()
{
    int width = 400;
    int height = 225;

    Camera camera(width, height, 100, 50);
    camera.setVFOV(20);
    camera.setOrientation(Point3(26, 3, 6), Point3(0, 2, 0), Vector3(0, 1, 0));
    camera.setAperture(0.0, 10.0);
    camera.setBackground(Colour(0, 0, 0));

    HittableList world;

    std::shared_ptr<Texture> perlinTexture = std::make_shared<NoiseTexture>(4.0);
    world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, std::make_shared<Lambertian>(perlinTexture)));
    world.add(std::make_shared<Sphere>(Point3(0, 2, 0), 2, std::make_shared<Lambertian>(perlinTexture)));

    std::shared_ptr<Material> diffuseLight = std::make_shared<DiffuseLight>(Colour(4.0, 4.0, 4.0));
    world.add(std::make_shared<Sphere>(Point3(0, 7, 0), 2, diffuseLight));
    world.add(std::make_shared<Quad>(Point3(3, 1, -2), Vector3(2, 0, 0), Vector3(0, 2, 0), diffuseLight));

    renderScene(width, height, camera, world);    
}

void cornellBox()
{
    int width = 600;
    int height = 600;

    Camera camera(width, height, 200, 50);
    camera.setVFOV(40);
    camera.setOrientation(Point3(278, 278, -800), Point3(278, 278, 0), Vector3(0, 1, 0));
    camera.setAperture(0.0, 10.0);
    camera.setBackground(Colour(0, 0, 0));

    HittableList world;

    std::shared_ptr<Material> red = std::make_shared<Lambertian>(Colour(0.65, 0.05, 0.05));
    std::shared_ptr<Material> white = std::make_shared<Lambertian>(Colour(0.73, 0.73, 0.73));
    std::shared_ptr<Material> green = std::make_shared<Lambertian>(Colour(0.12, 0.45, 0.15));
    std::shared_ptr<Material> light = std::make_shared<DiffuseLight>(Colour(15, 15, 15));

    world.add(std::make_shared<Quad>(Point3(555,0, 0), Vector3(0, 555, 0), Vector3(0, 0, 555), green));
    world.add(std::make_shared<Quad>(Point3(0,0, 0), Vector3(0, 555, 0), Vector3(0, 0, 555), red));
    world.add(std::make_shared<Quad>(Point3(343,554, 332), Vector3(-130, 0, 0), Vector3(0, 0, -105), light));
    world.add(std::make_shared<Quad>(Point3(0, 0, 0), Vector3(555, 0, 0), Vector3(0, 0, 555), white));
    world.add(std::make_shared<Quad>(Point3(555,555, 555), Vector3(-555, 0, 0), Vector3(0, 0, -555), white));
    world.add(std::make_shared<Quad>(Point3(0,0, 555), Vector3(555, 0, 0), Vector3(0, 555, 0), white));

    std::shared_ptr<Hittable> box1 = Quad::box(Point3(0, 0, 0), Point3(165, 330, 165), white);
    box1 = std::make_shared<RotateY>(box1, 15);
    box1 = std::make_shared<Translate>(box1, Vector3(265, 0, 295));
    world.add(box1);

    std::shared_ptr<Hittable> box2 = Quad::box(Point3(0, 0, 0), Point3(165, 165, 165), white);
    box2 = std::make_shared<RotateY>(box2, -10);
    box2 = std::make_shared<Translate>(box2, Vector3(130, 0, 65));
    world.add(box2);

    renderScene(width, height, camera, world);
}

void cornellSmoke()
{
    int width = 600;
    int height = 600;

    Camera camera(width, height, 200, 50);
    camera.setVFOV(40);
    camera.setOrientation(Point3(278, 278, -800), Point3(278, 278, 0), Vector3(0, 1, 0));
    camera.setAperture(0.0, 10.0);
    camera.setBackground(Colour(0, 0, 0));

    HittableList world;

    std::shared_ptr<Material> red = std::make_shared<Lambertian>(Colour(0.65, 0.05, 0.05));
    std::shared_ptr<Material> white = std::make_shared<Lambertian>(Colour(0.73, 0.73, 0.73));
    std::shared_ptr<Material> green = std::make_shared<Lambertian>(Colour(0.12, 0.45, 0.15));
    std::shared_ptr<Material> light = std::make_shared<DiffuseLight>(Colour(7, 7, 7));

    world.add(std::make_shared<Quad>(Point3(555,0, 0), Vector3(0, 555, 0), Vector3(0, 0, 555), green));
    world.add(std::make_shared<Quad>(Point3(0,0, 0), Vector3(0, 555, 0), Vector3(0, 0, 555), red));
    world.add(std::make_shared<Quad>(Point3(113,554, 127), Vector3(330, 0, 0), Vector3(0, 0, 105), light));
    world.add(std::make_shared<Quad>(Point3(0, 555, 0), Vector3(555, 0, 0), Vector3(0, 0, 555), white));
    world.add(std::make_shared<Quad>(Point3(0,0, 0), Vector3(555, 0, 0), Vector3(0, 0, 555), white));
    world.add(std::make_shared<Quad>(Point3(0,0, 555), Vector3(555, 0, 0), Vector3(0, 555, 0), white));

    std::shared_ptr<Hittable> box1 = Quad::box(Point3(0, 0, 0), Point3(165, 330, 165), white);
    box1 = std::make_shared<RotateY>(box1, 15);
    box1 = std::make_shared<Translate>(box1, Vector3(265, 0, 295));

    std::shared_ptr<Hittable> box2 = Quad::box(Point3(0, 0, 0), Point3(165, 165, 165), white);
    box2 = std::make_shared<RotateY>(box2, -10);
    box2 = std::make_shared<Translate>(box2, Vector3(130, 0, 65));

    world.add(std::make_shared<ConstantMedium>(box1, 0.01, Colour(0, 0, 0)));
    world.add(std::make_shared<ConstantMedium>(box2, 0.01, Colour(1, 1, 1)));

    renderScene(width, height, camera, world);
}

void finalScene(int width, int samplesPerPixel, int maxDepth)
{
    int height = width;

    Camera camera(width, height, samplesPerPixel, maxDepth);
    camera.setVFOV(40);
    camera.setOrientation(Point3(478, 278, -600), Point3(278, 278, 0), Vector3(0, 1, 0));
    camera.setAperture(0.0, 10.0);
    camera.setBackground(Colour(0, 0, 0));

    std::shared_ptr<Material> ground = std::make_shared<Lambertian>(Colour(0.48, 0.83, 0.53));
    std::shared_ptr<Material> light = std::make_shared<DiffuseLight>(Colour(7, 7, 7));
    std::shared_ptr<Material> sphereMaterial = std::make_shared<Lambertian>(Colour(0.7, 0.3, 0.1));
    std::shared_ptr<Material> emat = std::make_shared<Lambertian>(std::make_shared<ImageTexture>("earthmap.jpg"));
    std::shared_ptr<Material> white = std::make_shared<Lambertian>(Colour(0.73, 0.73, 0.73));

    std::shared_ptr<Texture> pertext = std::make_shared<NoiseTexture>(0.2);

    HittableList world, boxes1, boxes2;
    
    int boxesPerSide = 20;
    for (int i=0; i<boxesPerSide; i++) {
        for (int j=0; j<boxesPerSide; j++) {
            double w = 100.0;
            double x0 = -1000.0 + i*w;
            double y0 = 0.0;
            double z0 = -1000.0 + j*w;
            double x1 = x0 + w;
            double y1 = randomDouble(1, 101);
            double z1 = z0 + w;
            boxes1.add(Quad::box(Point3(x0, y0, z0), Point3(x1, y1, z1), ground));
        }
    }
    world.add(std::make_shared<BoundingVolumeHierarchyNode>(boxes1));

    world.add(std::make_shared<Quad>(Point3(123,554,142), Vector3(300, 0, 0), Vector3(0, 0, 265), light));

    Point3 centre1 = Point3(400, 400, 200);
    Point3 centre2 = centre1 + Vector3(30, 0, 0);
    world.add(std::make_shared<Sphere>(centre1, centre2, 50, sphereMaterial));

    world.add(std::make_shared<Sphere>(Point3(260, 150, 45), 50, std::make_shared<Dielectric>(1.5)));
    world.add(std::make_shared<Sphere>(Point3(0, 150, 145), 50, std::make_shared<Metal>(Colour(0.8, 0.8, 0.9), 1.0)));

    std::shared_ptr<Hittable> boundary = std::make_shared<Sphere>(Point3(360,150,145), 70, std::make_shared<Dielectric>(1.5));
    world.add(boundary);
    world.add(std::make_shared<ConstantMedium>(boundary, 0.2, Colour(0.2, 0.4, 0.9)));

    boundary = std::make_shared<Sphere>(Point3(0, 0, 0), 5000, std::make_shared<Dielectric>(1.5));
    world.add(std::make_shared<ConstantMedium>(boundary, 0.0001, Colour(1, 1, 1)));

    world.add(std::make_shared<Sphere>(Point3(400, 200, 400), 100, emat));

    world.add(std::make_shared<Sphere>(Point3(220.0, 280.0, 300.0), 80, std::make_shared<Lambertian>(pertext)));

    int ns = 1000;
    for (int j=0; j < ns; j++)
        boxes2.add(std::make_shared<Sphere>(Point3::random(0, 165), 10, white));

    world.add(std::make_shared<Translate>(std::make_shared<RotateY>(std::make_shared<BoundingVolumeHierarchyNode>(boxes2), 15), Vector3(-100, 270, 395)));

    renderScene(width, height, camera, world);
}

int main()
{
    int scene = 10;

    switch(scene) {
    case 0: sceneDepthOfField(); break;
    case 1: sceneBouncingSpheres(); break;
    case 2: sceneCheckeredSpheres(); break;
    case 3: sceneEarth(); break;
    case 4: perlinSpheres(); break;
    case 5: quads(); break;
    case 6: simpleLights(); break;
    case 7: cornellBox(); break;
    case 8: cornellSmoke(); break;
    case 9: finalScene(800, 10000, 40); break;
    default: finalScene(400, 250, 4); break;
    }

    return 0;
}