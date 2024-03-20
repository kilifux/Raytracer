#include "LightIntensity.h"

void LightIntensity::add(double R, double G, double B)
{
	r += R;
	g += G;
	b += B;
}

LightIntensity LightIntensity::operator+=(LightIntensity& li)
{
	r += li.r;
	g += li.g;
	b += li.b;

	return *this;
}

LightIntensity LightIntensity::operator-=(LightIntensity& li)
{
	r -= li.r;
	g -= li.g;
	b -= li.b;

	return *this;
}

LightIntensity LightIntensity::operator*=(float num)
{
	r *= num;
	g *= num;
	b *= num;

	return *this;
}

LightIntensity LightIntensity::operator/=(float num)
{
	r /= num;
	g /= num;
	b /= num;

	return *this;
}
