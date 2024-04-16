#include "Plane.h"

#include <iostream>

Vector Plane::GetIntersectionPoint()
{
    return intersectionPoint;
}

Vector Plane::Intersect(Ray ray) {

    float ndotD = normal.dotProduct(ray.Direction);
    if (ndotD == 0) {

        return Vector(-1000,-1000,-1000);
    }

    float t = (Center - ray.Origin).dotProduct(normal) / ndotD;
    if (t > 0 && (this->range == 0.0f || t < this->range)) {

        intersectionPoint = ray.Origin + (ray.Direction * t);
        intersectionNormal = normal;
        return Vector(t, t, t);
    }


    return Vector(-1000, -1000, -1000);
}

Vector Plane::GetIntersectionNormal() {
    return intersectionNormal;
}