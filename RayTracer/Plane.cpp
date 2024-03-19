#include "Plane.h"

#include <iostream>


bool Plane::Intersect(const Ray& ray, float range) {
    float ndotD = normal.dotProduct(ray.Direction);
    if (ndotD == 0) {
        std::cout << "Brak przeciecia" << std::endl;
        return false;
    }

    float t = -(normal.dotProduct(ray.Origin - center)) / ndotD;
    if (t > 0 && (range == 0.0f || t < range)) {
        std::cout << ray.Origin + (ray.Direction * t) << std::endl;
        return true;
    }

    std::cout << "Brak przeciecia" << std::endl;
    return false;
}

