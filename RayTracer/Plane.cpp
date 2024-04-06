#include "Plane.h"

#include <iostream>


Vector Plane::Intersect(Ray ray) {
    //std::cout << "plane " << std::endl;
    float ndotD = normal.dotProduct(ray.Direction);
    if (ndotD == 0) {
        //std::cout << "Brak przeciecia" << std::endl;
        return Vector(-1000,-1000,-1000);
    }

    //float t = -(normal.dotProduct(ray.Origin - center)) / ndotD;
    float t = (center - ray.Origin).dotProduct(normal) / ndotD;
    if (t >= 0 && (this->range == 0.0f || t < this->range)) {
        //std::cout << ray.Origin + (ray.Direction * t) << std::endl;
        Vector result = ray.Origin + (ray.Direction * t);
        float len = result.GetLength();
        return Vector(t,t,t);
    }

    //std::cout << "Brak przeciecia" << std::endl;
    return Vector(-1000, -1000, -1000);
}

