#include "Plane.h"


bool Plane::Intersects(const Ray& ray, float range) {
    float ndotD = normal.dotProduct(ray.Direction);
    if (ndotD == 0)
        return false;

    float t = -(normal.dotProduct(ray.Origin - center)) / ndotD;
    if (t > 0 && (range == 0.0f || t < range)) {
        return true;
    }

    return false;
}

