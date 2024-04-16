#pragma once

#include "Vector.h"
#include "Ray.h"
#include "Object.h"

class Plane : public Object{
public:
    Vector normal;
    Vector Center;
    //Vector colour = Vector(0.0f,0.0f,0.0f);
    //Material material;
    Vector intersectionPoint;
    Vector intersectionNormal;

    float range = 100.0f;

    Plane();
    Plane(const Vector& center, const Vector& normal, Material material) : Center(center), normal(normal), Object(material) {}

    Vector Intersect(Ray ray);
    Vector GetIntersectionPoint();
    Vector GetIntersectionNormal();
};