#include "Object.h"

Object::Object(Vector colour)
{
	this->colour = colour;
}

bool Object::Intersect(Ray ray)
{
	return true;
}

Vector Object::GetColour()
{
	return colour;
}