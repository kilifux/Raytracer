#pragma once
#include "Light.h"
#include "PointLight.h"

class SurfaceLight : public Light
{
public:
	float constAtten;
	float linearAtten;
	float quadAtten;
	std::vector<std::shared_ptr<Light>> lights;
	Vector v, w;
	int lightDensity = 10;

	SurfaceLight(Vector position, LightIntensity lightIntensity, float constAtten, float linearAtten, float quadAtten, Vector v, Vector w, int lightDens)
		: Light(position, lightIntensity), constAtten(constAtten), linearAtten(linearAtten), quadAtten(quadAtten), v(v), w(w), lightDensity(lightDens) 
	{
		Vector stepV = v / lightDens;
		Vector stepW = w / lightDens;

		//std::cout << stepV * 30 << std::endl;

		Vector lightPos = Vector(0, 0, 0);

		for (int i = 0; i < lightDens; i++) {
			for (int j = 0; j < lightDens; j++) {
				lightPos = position + stepV * i + stepW * j;
				lights.push_back(std::make_shared<PointLight>(
					lightPos,
					lightIntensity,
					constAtten,
					linearAtten,
					quadAtten
					));
			}
		}
		
		//std::cout << lights.size() << std::endl;
	}

	Vector calculateLightingColor(std::vector<std::shared_ptr<Object>> objects, Vector IntersectionPoint, std::shared_ptr<Object> closestObject, Vector cameraDir, int nr);
};

