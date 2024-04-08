#pragma once
#include "Light.h"
#include "Object.h"

class SpotLight : public Light
{
public:
	float constAtten;
	float linearAtten;
	float quadAtten;

	SpotLight(Vector position, LightIntensity lightIntensity, float constAtten, float linearAtten, float quadAtten) 
		: Light(position, lightIntensity), constAtten(constAtten), linearAtten(linearAtten), quadAtten(quadAtten){}


	virtual Vector calculateLightingColor(std::vector<std::shared_ptr<Object>> objects, Vector IntersectionPoint, std::shared_ptr<Object> closestObject, Vector cameraDir, int nr) override;

};

