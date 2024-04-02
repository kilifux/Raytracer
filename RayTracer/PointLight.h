#pragma once
#include "Light.h"


class PointLight : public Light {

public:
	Vector location;
	float constAtten;
	float linearAtten;
	float quadAtten;


	Vector getDiffuse(Vector cameraPosition);
	Vector getSpecular(Vector cameraPosition);
	int isInShadow();
};

