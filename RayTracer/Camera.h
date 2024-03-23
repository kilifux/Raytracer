#pragma once
#include "Vector.h"
#include "Ray.h"

class Camera
{
	Vector position;
	Vector target;
	Vector up;

	int resolutionX = 512;
	int resolutionY = 512;

public:

	Camera(int resX, int resY, Vector position, Vector target, Vector up);

	int GetResolutionX();
	int GetResolutionY();

	Vector GetPosition();
	Vector GetTarget();
	Vector GetUp();

	Ray GenerateRay(float x, float y);
};

