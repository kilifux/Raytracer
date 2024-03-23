#include "OrthographicCamera.h"


int OrthographicCamera::GetResX()
{
	return this->GetResolutionX();
}

int OrthographicCamera::GetResY()
{
	return this->GetResolutionY();
}

Vector OrthographicCamera::GetCameraTarget()
{
	return GetTarget();
}

Vector OrthographicCamera::GetPos()
{
	return GetPosition();
}

Ray OrthographicCamera::GenerateRay(float x, float y)
{
	float pixelWidth = 2.0f / this->GetResX();
	float pixelHeight = 2.0f / this->GetResY();

	float centreX = -1.0f + (x + 0.5f) * pixelWidth;
	float centreY = 1.0f - (y + 0.5f) * pixelHeight;

	Ray r1 = Ray(Vector(centreX + GetPos().x, centreY + GetPos().y, 0), GetCameraTarget());

	//std::cout << r1.Direction << " " << r1.Origin << std::endl;

	return r1;
}
