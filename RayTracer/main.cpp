#include <iostream>
#include <fstream>
#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"

Vector color(Ray& r, Sphere& sphere, Triangle& triangle, Plane& plane);

int main(int argv, char** args) {

    /*auto aspect_ratio = 16.0 / 9.0;
    int image_width = 100;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    auto camera_center = Vector(0, 0, 15);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = Vector(viewport_width, 0, 0);
    auto viewport_v = Vector(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
        - Vector(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;

    Sphere sphere(Vector(0.f, 0.f, 0.f), 10.f);
    Triangle triangle(Vector(0.0f, 0.0f, 0.0f), Vector(1.0f, 0.0f, 0.0f), Vector(0.0f, 1.0f, 0.0f));
    Plane plane(Vector(0, 2, -5), Vector(0, 1, 0));

    std::ofstream MyFile("test.ppm");
    MyFile << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 00; j--)
    {
        for (int i = 0; i < image_width; i++)
        {
            auto pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);

            Vector col = color(r, sphere, triangle, plane);
            Vector wektorIRGB(int(255.99 * col.x), int(255.99 * col.y), int(255.99 * col.z));

            MyFile << wektorIRGB.x << " " << wektorIRGB.y << " " << wektorIRGB.z << "\n";
        }
    }


    MyFile.close(); */


    //Zadanie 1


    Vector first(0, 3, 0);
    Vector second(5, 5, 0);
    Vector result = second + first;

    std::cout << "2. " << result << std::endl;

    std::cout << "3. " << second.getAngle(first) << std::endl;

    Vector one(4, 5, 1);
    Vector two(4, 1, 3);
    Vector result2 = one.cross(two);

    std::cout << "4. " << result2 << std::endl;

    std::cout << "5. " << result2.Normalize() << std::endl;

    Vector RayOrigin(0, 0, -20);
    Sphere sphere(Vector(0, 0, 0), 10);
    Ray ray(RayOrigin, -RayOrigin.Normalize());
    Ray ray2(RayOrigin, Vector(0, 1, 0));

    std::cout << "10 and 11. R1 ";
    sphere.Intersect(ray, 0, 20);
    std::cout << "10. R2 ";
    sphere.Intersect(ray2, 0, 20);

    std::cout << "12. R3 ";
    Ray ray3(Vector(0, 0, -20), Vector(0, 0, 1));
    sphere.Intersect(ray3, 0, 200);

    std::cout << "14. Plane: ";
    Plane plane(Vector(0, 0, 0), Vector(0, 1, 1).Normalize());
    plane.Intersect(ray2, 50);

    std::cout << "\nTriangles" << std::endl;

    Triangle triangle(Vector(0, 0, 0), Vector(1, 0, 0), Vector(0, 1, 0));
    Ray R4 = Ray::GetTwoPointsRay(Vector(-1, 0.5, 0), Vector(1, 0.5, 0));

    Vector intersectionPoint;

    std::cout << triangle.Intersect(R4, intersectionPoint) << std::endl;

    Ray R5 = Ray::GetTwoPointsRay(Vector(2, -1, 0), Vector(2, 2, 0));
    std::cout << triangle.Intersect(R5, intersectionPoint) << std::endl;

    Ray R6 = Ray::GetTwoPointsRay(Vector(0, 0, -1), Vector(0, 0, 1));
    std::cout << triangle.Intersect(R6, intersectionPoint) << std::endl;
    std::cout << intersectionPoint << std::endl;
    return 0;
}


Vector color(Ray& r, Sphere& sphere, Triangle& triangle, Plane& plane) {
    r.Direction.Normalize();
    Vector unitDir = r.Direction;
    Vector IntersectVector(0.0f, 0.0f, 0.0f);
    float t = 0.5f * (unitDir.y + 1.0f);

    if (plane.Intersect(r, 10))
        return Vector(0, 0, 1);

    if (sphere.Intersect(r, 0, 10))
        return Vector(1.0, 0.5, 1.0);


    if (triangle.Intersect(r, IntersectVector))
        return Vector(1.0f, 1.0f, 0.5f);


    return Vector(1.0, 1.0, 1.0) * (1.0 - t) + Vector(0.5, 0.7, 1.0f) * t;
}
