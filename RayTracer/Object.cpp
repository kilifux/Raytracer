#include "Object.h"



Object::Object(Material material)
{
	this->material = material;
}

Vector Object::Intersect(Ray ray)
{
	return Vector(-1000,-1000,-1000);
}



Material Object::GetMaterial()
{
	return this->material;
}

Vector Object::GetIntersectionPoint() {
	return intersectionPoint;
}