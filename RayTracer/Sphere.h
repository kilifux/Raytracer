#pragma once

#include "Vector.h"
#include "Ray.h"

class Sphere {
public:

    Vector Center;
    float Radius;

    Sphere() {};
    Sphere(float r) : Radius(r) {};
    Sphere(Vector v, float r) : Center(v), Radius(r) {}

    bool Intersect(Ray ray, float t_min, float t_max) const;


};

