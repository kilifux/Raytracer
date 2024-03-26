#pragma once
#include "Camera.h"

class OrthographicCamera : public Camera
{
public:

	OrthographicCamera(int resX, int resY, Vector position, Vector target = { 0, 0, -1 }, Vector up = { 0, 1, 0 }) :
		Camera(resX, resY, position, target.Normalize(), up) {}

	//OrthographicCamera(OrthographicCamera& camera);

	int GetResX();
	int GetResY();

	Vector GetCameraTarget();
	Vector GetPos();
	Vector GetCameraUp();

	virtual Ray GenerateRay(float x, float y);
};

