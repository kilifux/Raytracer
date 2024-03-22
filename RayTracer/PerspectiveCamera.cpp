#include "PerspectiveCamera.h"
#define M_PI 3.14159265358979323846

int PerspectiveCamera::GetResX()
{
	return this->GetResolutionX();
}

int PerspectiveCamera::GetResY()
{
	return this->GetResolutionY();
}

Vector PerspectiveCamera::GetPos()
{
	return this->GetPosition();
}

Vector PerspectiveCamera::GetCameraTarget()
{
	return GetTarget();
}


Ray PerspectiveCamera::GenerateRay(int x, int y)
{
	
	float aspect = GetResX() / GetResY();
	// Find the half-height and half-width
	float hh = tan((FOV * M_PI / 360) / 2.0) * farPlane;
	float hw = aspect * hh;

	float l, r, t, b;
	l = -hw; r = hw;
	b = -hh; t = hh;

	// mapping pixels to screen space
	float u = l + ((r - l) * (x + 0.5)) / GetResX();
	float v = b + ((t - b) * (y + 0.5)) / GetResY();

	// determining the Camera frame
	Vector gaze = GetCameraTarget() - GetPos();

	Vector w = -gaze;
	w = w.Normalize();

	Vector uVec = GetUp().cross(w);
	uVec = uVec.Normalize();

	Vector vVec = w.cross(uVec);
	vVec = vVec.Normalize();

	Vector e = GetPos();

	// Generating the ray
	Vector o = e; //<! ray's origin
	Vector d = w  * -(farPlane) + uVec * u + vVec * v; //<! ray's direction


	Ray ray = Ray(o, d);

	return ray;
}
