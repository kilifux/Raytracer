#include "PerspectiveCamera.h"
#define M_PI 3.14159265358979323846


Ray PerspectiveCamera::GenerateRay(int x, int y)
{
	int resX = GetResolutionX();
	int resY = GetResolutionY();
	float FOVY = FOV * M_PI / 360;
	float PX = (2 * ((x + 0.5f) / resX) - 1) * (resX / resY) * tan(FOVY);
	float PY = (1 - 2 * ((y + 0.5f) / resY)) * tan(FOVY);
	/*
	Vector3 dir = Vector3(PX, PY, -1) - this->_position;
	dir.normalize();
	*/

	float fLenght = sin(90 - FOVY) / sin(FOVY);

	Vector gaze = GetTarget() - GetPosition();

	Vector w = gaze * -1;
	w.Normalize();

	Vector sx = w.cross(GetUp());
	sx.Normalize();
	//sx = sx * tan(FOVY);

	Vector sy = sx.cross(w);
	sy.Normalize();
	//sy = sy * tan(FOVY);

	float ww = tan(FOVY);

	Vector dir = sx * PX + sy * PY;
	dir = dir + w * fLenght;

	dir.Normalize();

	//std::cout << dir << "\n";

	return Ray(GetPosition(), dir);
}
