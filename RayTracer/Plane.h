#pragma once

#include "Vector.h"
#include "Ray.h"
#include "Object.h"

class Plane {
public:
    Vector normal;
    Vector center;
    Vector colour = Vector(0.0f,0.0f,0.0f);

    float range = 100.0f;

    Plane();
    Plane(const Vector& center, const Vector& normal, Vector colour) : center(center), normal(normal) {}

    bool Intersect(const Ray& ray);

};