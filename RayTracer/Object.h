#pragma once
#include "Ray.h"

class Object
{
public:
	Vector Center;
	Vector colour = Vector(0.7,0.3,0.5);
	Vector intersectionPoint;

	Object(Vector colour);
	virtual Vector Intersect(Ray ray);
	//virtual bool Intersect(Ray ray, Vector& intersectionPoint);
	Vector GetColour();
	Vector GetIntersectionPoint();
};

