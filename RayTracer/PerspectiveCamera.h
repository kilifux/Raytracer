#pragma once
#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:

	float FOV;
	float nearPlane;
	float farPlane;

	Vector screenPosition;

	int GetResX();
	int GetResY();

	Vector GetPos();
	Vector GetCameraTarget();

	PerspectiveCamera(int resX, int resY, float nearPlane, float farPlane, float FOV, Vector position, Vector target = { 0, 0, -1 }, Vector up = { 0, 1, 0 })
		: nearPlane(nearPlane), farPlane(farPlane), FOV(FOV), Camera(resX, resY, position, target.Normalize(), up) {}

	Ray GenerateRay(float x, float y);


};

