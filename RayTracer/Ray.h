#pragma once

#include "Vector.h"

class Ray
{
public:
    Vector Origin;
    Vector Direction;

    Ray();
    Ray(const Vector& origin, const Vector& direction) : Origin(origin), Direction(direction) { }
    Vector pointAtParameter(float t) const { return Origin + Direction * t; }
};

