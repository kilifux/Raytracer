#pragma once
#include "Ray.h"
#include "Material.h"

class Object
{
public:
	Vector Center;
	Vector intersectionPoint;
	Material material;

	Object(Material material);
	virtual Vector Intersect(Ray ray);

	Material GetMaterial();
	virtual Vector GetIntersectionPoint();

	virtual Vector GetNormalAt(const Vector& point) const = 0;
};

