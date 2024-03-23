#pragma once
#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:

	float FOV;
	float planeDist;

	Vector screenPosition;

	int GetResX();
	int GetResY();

	Vector GetPos();
	Vector GetCameraTarget();

	PerspectiveCamera(int resX, int resY, float farPlane, float FOV, Vector position, Vector target = { 0, 0, -1 }, Vector up = { 0, 1, 0 })
		: planeDist(farPlane), FOV(FOV), Camera(resX, resY, position, target.Normalize(), up) {}

	Ray GenerateRay(float x, float y);


};

