#include "Material.h"

Material::Material()
{
	colour = Vector(0.5,0.5,0.5);
}

Material::Material(Vector color)
{
	this->colour = color;
}

Material::Material(Vector colour, float specularAmount, float specularCoeff, float reflectFraction, float refractFraction)
{
	this->colour = colour;
	this->specularAmount = specularAmount;
	this->specularCoeff = specularCoeff;
	this->reflectFraction = reflectFraction;
	this->refractFraction = refractFraction;
}

void Material::SetColour(Vector colour)
{
	this->colour = colour;
}

Vector Material::GetColour()
{
	return this->colour;
}
