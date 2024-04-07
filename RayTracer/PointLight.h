#pragma once
#include "Light.h"


class PointLight : public Light {

public:

	Vector color;
	float intensity;

	float constAtten = 0.4f;
	float linearAtten = 0.1f;
	float quadAtten = 0.1f;


	PointLight(Vector position, LightIntensity lightIntensity, float intensity) : Light(position, lightIntensity), intensity(intensity){}
	PointLight(Vector position, LightIntensity lightIntensity) : Light(position, lightIntensity), intensity(1.f) {}
	virtual Vector calculateLightingColor(std::vector<std::shared_ptr<Object>> objects, Vector IntersectionPoint, std::shared_ptr<Object> closestObject, Vector cameraDir) override;
	Vector getDiffuse(Vector cameraPosition);
	Vector getSpecular(Vector cameraPosition);
	bool isInShadow(std::vector<std::shared_ptr<Object>> objects, Vector intersectionPoint);
};

