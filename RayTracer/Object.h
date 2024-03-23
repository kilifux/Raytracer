#pragma once
#include "Ray.h"

class Object
{
public:

	virtual bool Intersect(Ray ray);
};

