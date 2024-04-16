#pragma once
#include "Vector.h"

class Material
{
private:
	Vector colour = Vector(0.3,0.3,0.3);

public:

	float specularAmount = 0.0f;
	float specularCoeff = 0.0f;
	float reflectFraction = 0.0f;
	float refractFraction = 0.0f;

	Material();
	Material(Vector color);
	Material(Vector color, float specular_amount, float specular_coeff, float reflect_fraction, float refract_fraction);
	void SetColour(Vector colour);
	Vector GetColour();
};

