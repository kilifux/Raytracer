#pragma once
#include "Camera.h"

class PerspectiveCamera : Camera
{
public:

	float FOV;
	float nearPlane;
	float farPlane;

	PerspectiveCamera(float FOV, float nearPlane, float farPlane, Vector position, Vector target, Vector up);

	virtual Ray GenerateRay(int x, int y);

};

