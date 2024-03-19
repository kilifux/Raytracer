#include <iostream>
#include <fstream>
#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"

Vector color(Ray& r, Sphere& sphere, Triangle& triangle, Plane& plane);

int main(int argv, char** args) {


    //Zadanie 1

    Vector first(0, 3, 0);
    Vector second(5, 5, 0);
    Vector result = first + second;
    Vector result2 = second + first;

    std::cout << "2. [0,3,0] + [5,5,0] = " << result << std::endl;
    std::cout << "   [5,5,0] + [0,3,0] = " << result2 << std::endl;

    std::cout << "3. Angle between [0,3,0] and [5,5,0] = " << second.getAngle(first) << std::endl;

    Vector one(4, 5, 1);
    Vector two(4, 1, 3);
    Vector result3 = one.cross(two);

    std::cout << "4. Vector perpendicular to [4,5,1] and [4,1,3] = " << result3 << std::endl;

    std::cout << "5. Normlaized perpendicualr vector = " << result3.Normalize() << std::endl;

    Vector RayOrigin(0, 0, -20);
    Sphere sphere(Vector(0, 0, 0), 10);
    Ray ray(RayOrigin, -RayOrigin.Normalize());
    Ray ray2(RayOrigin, Vector(0, 1, 0));

    std::cout << "10 and 11. Intersection of Sphere and R1 : ";
    sphere.Intersect(ray, 0, 20);
    std::cout << "10. Intersection of Sphere and R2 : ";
    sphere.Intersect(ray2, 0, 20);

    std::cout << "12. Intersection of Sphere and R3 : ";
    Ray ray3(Vector(0,15,0), Vector(0,-15,0));
    sphere.Intersect(ray3, 0, 200);

    std::cout << "14. Plane: ";
    Plane plane(Vector(0, 0, 0), Vector(0, 1, 1).Normalize());
    plane.Intersect(ray2, 50);

    //std::cout << "\nTriangles" << std::endl;

    Triangle triangle(Vector(0, 0, 0), Vector(1, 0, 0), Vector(0, 1, 0));
    Ray R4(Vector(-1, 0.5, 0), Vector(1, 0.5, 0));

    Vector intersectionPoint;

    std::cout << "15.1. Intersection of Traingle and Ray([-1,0.5,0],[1,0.5,0]): ";

    std::cout << triangle.Intersect(R4, intersectionPoint) << std::endl;


    std::cout << "15.2. Intersection of Traingle and Ray([2,-1,0],[2,2,0]): ";
    Ray R5(Vector(2, -1, 0), Vector(2, 2, 0));
    std::cout << triangle.Intersect(R5, intersectionPoint) << std::endl;

    std::cout << "15.3. Intersection of Traingle and Ray([0,0,-1],[0,0,1]): ";
    Ray R6(Vector(0, 0, -1), Vector(0, 0, 1));
    std::cout << triangle.Intersect(R6, intersectionPoint) << " " << intersectionPoint << std::endl;

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
