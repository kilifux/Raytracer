#pragma once

#include "Vector.h"
#include "Ray.h"

class Triangle {

public:
    Vector vertices[3];
    Vector normals[3];

    Triangle() {}
    Triangle(const Vector& vertex1, const Vector& vertex2, const Vector& vertex3);
    Triangle(const Vector& vertex1, const Vector& vertex2, const Vector& vertex3,
        const Vector& normal1, const Vector& normal2, const Vector& normal3);

    bool IntersectTriangle(const Ray& ray, const Vector& A, const Vector& B, const Vector& C, Vector& intersectionPoint);

};



