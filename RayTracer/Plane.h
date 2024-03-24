#pragma once

#include "Vector.h"
#include "Ray.h"

class Plane {
public:
    Vector normal;
    Vector center;

    float range = 100.0f;

    Plane();
    Plane(const Vector& center, const Vector& normal) : center(center), normal(normal) {}

    bool Intersect(const Ray& ray);

};