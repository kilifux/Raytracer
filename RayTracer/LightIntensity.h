#pragma once
#include <ostream>

class LightIntensity
{
protected:
	double r, g, b;

public:
	LightIntensity(double R, double G, double B) : r(R), g(G), b(B) {}
	LightIntensity(double R, double G) : r(R), g(G), b(0) {}
	LightIntensity(double R) : r(R), g(0), b(0) {}
	LightIntensity() : r(0), g(0), b(0) {}

	double gRed() { return r; }
	double gGreen() { return g; }
	double gBlue() { return b; }

	void operator()(float R, float G, float B) { r = R; g = G; b = B; }
	void operator()(float R, float G) { r = R; g = G; b = 0.0; }
	void operator()(float R) { r = R; g = b = 0.0; }

	void add(double R, double G, double B);

	LightIntensity operator+(LightIntensity& li) { return { r + li.r, g + li.g, b + li.b }; }
	LightIntensity operator-(LightIntensity& li) { return { r - li.r, g - li.g, b - li.b }; }
	LightIntensity operator/(float num) { return { r / num , g / num, b / num }; }

	LightIntensity operator+=(LightIntensity& li);
	LightIntensity operator-=(LightIntensity& li);
	LightIntensity operator*=(float num);
	LightIntensity operator/=(float num);

	friend LightIntensity operator*(float num, LightIntensity& li) { return LightIntensity(li.r * num, li.g * num, li.b * num); }
	friend LightIntensity operator*(LightIntensity& li, float num) { return LightIntensity(li.r * num, li.g * num, li.b * num); }
	friend std::ostream& operator<<(std::ostream& str, LightIntensity& li) { return str << "Light intensity: r - " << li.r << ", g - " << li.g << ", b - " << li.b; }

};
