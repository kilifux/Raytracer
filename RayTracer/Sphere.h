#pragma once

#include "Vector.h"
#include "Ray.h"
#include "Object.h"

class Sphere : Object {
public:

    Vector Center;
    float Radius;
    Vector colour = Vector(0.0f, 0.0f, 0.0f);

    Sphere() {};
    Sphere(float r, Vector colour) : Radius(r), colour(colour) {};
    Sphere(Vector v, float r, Vector colour) : Center(v), Radius(r), colour(colour) {}

    bool Intersect(Ray ray, float t_min, float t_max) const;


};

