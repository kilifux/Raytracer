#pragma once
#include "Vector.h"
#include <vector>
#include "Object.h"
#include "LightIntensity.h"

class Light
{
public:
	Vector position;
	LightIntensity lightIntensity;

	Light(Vector position, LightIntensity lightIntensity) : position(position), lightIntensity(lightIntensity){}

	virtual Vector calculateLightingColor(std::vector<std::shared_ptr<Object>> objects, Vector IntersectionPoint, std::shared_ptr<Object> closestObject, Vector cameraDir)
	{
		return { 0.f, 0.f, 0.f };
	}
};

