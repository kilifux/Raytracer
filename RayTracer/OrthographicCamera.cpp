#include "OrthographicCamera.h"


int OrthographicCamera::GetResX()
{
	return this->GetResolutionX();
}

int OrthographicCamera::GetResY()
{
	return this->GetResolutionY();
}

Ray OrthographicCamera::GenerateRay(int x, int y)
{
	float pixelWidth = 2.0f / this->GetResolutionX();
	float pixelHeight = 2.0f / this->GetResolutionY();

	float centreX = -1.0f + (x + 0.5f) * pixelWidth;
	float centreY = -1.0f - (y + 0.5f) * pixelHeight;

	return Ray(Vector(centreX + GetPosition().x, centreY + GetPosition().y, 0), GetTarget());
}
