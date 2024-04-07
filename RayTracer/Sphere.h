#pragma once

#include "Vector.h"
#include "Ray.h"
#include "Object.h"

class Sphere : public Object {
public:

    Vector Center;
    float Radius;
    //Vector colour = Vector(0.0f, 0.0f, 0.0f);
    Vector intersectionPoint;

    float t_max = 100.0f;
    float t_min = 0.01f;

    //Sphere() {};
    Sphere(float r, Material material) : Radius(r), Object(material) {};
    Sphere(Vector v, float r, Material material) : Center(v), Radius(r), Object(material) {}

    Vector GetIntersectionPoint();

    Vector Intersect(Ray ray);

    virtual Vector GetNormalAt(const Vector& point) const override;

    //bool Intersect(Ray ray, Vector& intersectionPoint);

    //bool Intersect(Ray ray);


};

