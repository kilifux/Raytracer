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

bool Triangle::IntersectTriangle(Ray& ray, Vector& intersectionPoint) {

    const float EPSILON = 0.0000001;

    Vector AB = vertices[1] - vertices[0];
    Vector AC = vertices[2] - vertices[0];

    Vector pvec = ray.Direction.cross(AC);
    float dot = AB.dotProduct(pvec);

    if (fabs(dot) < EPSILON) {
        //std::cout << "parallel" << std::endl;
        return false;
    }
    float invDot = 1.0f / dot;

    Vector tvec = ray.Origin - vertices[0];
    float u = invDot * tvec.dotProduct(pvec);

    if (u < 0.0 || u > 1.0) {
        return false;
    }
    Vector qvec = tvec.cross(AB);
    float v = invDot * ray.Direction.dotProduct(qvec);

    if (v < 0.0 || u + v > 1.0) {
        return false;
    }

    float t = invDot * AC.dotProduct(qvec);

    if (t > EPSILON)
    {
        intersectionPoint = ray.Origin + ray.Direction * t;
        return true;
    }

    return false;

}
