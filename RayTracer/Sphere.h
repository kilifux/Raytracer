#pragma once

#include "Vector.h"
#include "Ray.h"
#include "Object.h"

class Sphere : public Object {
public:

    Vector Center;
    float Radius;
    Vector colour = Vector(0.0f, 0.0f, 0.0f);

    float t_max = 100.0f;
    float t_min = 0.1f;

    //Sphere() {};
    Sphere(float r, Vector colour) : Radius(r), colour(colour), Object(colour) {};
    Sphere(Vector v, float r, Vector colour) : Center(v), Radius(r), colour(colour), Object(colour) {}

    Vector GetColour();

    bool Intersect(Ray ray);


};

