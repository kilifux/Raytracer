#include "Triangle.h"
#include <cmath>

Triangle::Triangle(const Vector& vertex1, const Vector& vertex2, const Vector& vertex3) {
    vertices[0] = vertex1;
    vertices[1] = vertex2;
    vertices[2] = vertex3;

}

Triangle::Triangle(const Vector& vertex1, const Vector& vertex2, const Vector& vertex3, const Vector& normal1,
    const Vector& normal2, const Vector& normal3) {

    vertices[0] = vertex1;
    vertices[1] = vertex2;
    vertices[2] = vertex3;

    normals[0] = normal1;
    normals[1] = normal2;
    normals[2] = normal3;
}

bool Triangle::IntersectTriangle(const Ray& ray, const Vector& A, const Vector& B, const Vector& C,
    Vector& intersectionPoint) {

    Vector AB = B - A;
    Vector AC = C - A;
    Vector normal = AB.cross(AC);

    float dot = normal.dotProduct(ray.Direction);
    if (fabsf(dot) < 0.00000001)
        return false;

    float t = normal.dotProduct(A - ray.Origin) / dot;

    if (t < 0.0f)
        return false;

    intersectionPoint = ray.Origin + ray.Direction * t;

    Vector AP = intersectionPoint - A;
    Vector BP = intersectionPoint - B;
    Vector CP = intersectionPoint - C;

    Vector v1 = AB.cross(AP);
    Vector v2 = AC.cross(BP);
    Vector v3 = (B - C).cross(CP);

    if (v1.dotProduct(normal) >= 0.0f && v2.dotProduct(normal) >= 0.0f && v3.dotProduct(normal) >= 0.0f)
    {
        return true;
    }

    return false;

}
