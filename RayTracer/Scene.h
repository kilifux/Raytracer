#pragma once
#include "Object.h"
#include <vector>
#include "Camera.h"

class Scene
{
public:
	std::vector<std::shared_ptr<Object>> objects;
	std::shared_ptr<Camera> camera;
};

