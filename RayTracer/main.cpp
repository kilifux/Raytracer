#include <iostream>
#include <fstream>
#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"

Vector color(Ray& r, Sphere& sphere, Triangle& triangle, Plane& plane);

int main(int argv, char** args) {

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 1000;

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


    MyFile.close();

    return 0;
}


Vector color(Ray& r, Sphere& sphere, Triangle& triangle, Plane& plane) {
    r.Direction.Normalize();
    Vector unitDir = r.Direction;
    Vector IntersectVector(0.0f, 0.0f, 0.0f);
    float t = 0.5f * (unitDir.y + 1.0f);

    if (plane.Intersects(r, 10))
        return Vector(0, 0, 1);

    if (sphere.Hit(r, 0, 10))
        return Vector(1.0, 0.5, 1.0);


    if (triangle.IntersectTriangle(r, triangle.vertices[0], triangle.vertices[1], triangle.vertices[2], IntersectVector))
        return Vector(1.0f, 1.0f, 0.5f);


    return Vector(1.0, 1.0, 1.0) * (1.0 - t) + Vector(0.5, 0.7, 1.0f) * t;
}
