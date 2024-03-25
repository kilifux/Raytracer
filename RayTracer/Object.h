#pragma once
#include "Ray.h"

class Object
{
public:
	Vector Center;
	Vector colour = Vector(0.7,0.3,0.5);

	Object(Vector colour);
	virtual bool Intersect(Ray ray);
	Vector GetColour();
};

