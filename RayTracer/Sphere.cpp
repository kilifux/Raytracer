#include <cmath>
#include "Sphere.h"

bool Sphere::Hit(Ray ray, float t_min, float t_max) const {

    Vector oc = ray.Origin - Center;

    float a = ray.Direction.dotProduct(ray.Direction);
    float b = oc.dotProduct(ray.Direction);
    float c = oc.dotProduct(oc) - Radius * Radius;

    float discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        float temp = (-b - std::sqrtf(discriminant)) / a;

        if (temp < t_max && temp > t_min)
            return true;

        temp = (-b + std::sqrtf(discriminant)) / a;

        if (temp < t_max && temp > t_min)
            return true;
    }

    return false;
}
