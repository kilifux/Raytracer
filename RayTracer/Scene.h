#pragma once
#include "Object.h"
#include <vector>
#include "Camera.h"
#include "Light.h"

class Scene
{
public:
	std::vector<std::shared_ptr<Object>> objects;
	std::vector<std::shared_ptr<Light>> lights;
	int reflectionNumber = 1;

	std::shared_ptr<Camera> camera;

	Vector Light(Vector IntersectionPoint, std::shared_ptr<Object> closestObject, Vector cameraDir, int nr);
};

