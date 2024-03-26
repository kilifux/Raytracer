#include "Object.h"

Object::Object(Vector colour)
{
	this->colour = colour;
}

Vector Object::Intersect(Ray ray)
{
	return Vector(-1000,-1000,-1000);
}



Vector Object::GetColour()
{
	return colour;
}

Vector Object::GetIntersectionPoint() {
	return intersectionPoint;
}