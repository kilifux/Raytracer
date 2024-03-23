#pragma once
#include "Camera.h"

class OrthographicCamera : public Camera
{
public:

	OrthographicCamera(int resX, int resY, Vector position, Vector target, Vector up) :
		Camera(resX, resY, position, target.Normalize(), up) {}

	//OrthographicCamera(OrthographicCamera& camera);

	int GetResX();
	int GetResY();

	Vector GetCameraTarget();
	Vector GetPos();

	virtual Ray GenerateRay(float x, float y);
};

