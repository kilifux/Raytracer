#include "Camera.h"

Camera::Camera(int resX, int resY, Vector position, Vector target, Vector up)
{
	this->position = position;
	this->target = target;
	this->up = up;

	resolutionX = resX;
	resolutionY = resY;

}

int Camera::GetResolutionX()
{
	return resolutionX;
}

int Camera::GetResolutionY()
{
	return resolutionY;
}

Vector Camera::GetPosition()
{
	return this->position;
}

Vector Camera::GetTarget()
{
	return this->target;
}

Vector Camera::GetUp()
{
	return this->up;
}


Ray Camera::GenerateRay(float x, float y)
{
	return Ray(Vector(x, y, 1), Vector(x, y, 10));
}
