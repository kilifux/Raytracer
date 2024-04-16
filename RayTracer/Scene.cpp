#include "Scene.h"

Vector Scene::Light(Vector IntersectionPoint, std::shared_ptr<Object> closestObject, Vector cameraDir, int nr)
{
    Vector color = { 0, 0, 0 };

    for (auto &light : lights)
    {
        color = color + light->calculateLightingColor(objects, IntersectionPoint, closestObject, cameraDir, nr);
    }

    if (lights.size() > 0)
    {
        color = color / lights.size();
    }

    return color;
}
