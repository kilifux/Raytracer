#include "SpotLight.h"
#include <algorithm> 

Vector SpotLight::calculateLightingColor(std::vector<std::shared_ptr<Object>> objects, Vector IntersectionPoint, std::shared_ptr<Object> closestObject, Vector cameraDir)
{
    bool shadow = false;
    float dist = (position - IntersectionPoint).GetLength();

    Ray nRay = Ray(position, IntersectionPoint);

    //for (int i = 0; i < objects.size(); i++) {
    //    std::shared_ptr<Object> s = objects[i];
    //    Vector res = s->Intersect(nRay);
    //    
    //    if (dist - res.GetLength() > 0.1f) {
    //        shadow = true;
    //        break;
    //    }
    //   
    //}

    Vector color = closestObject->GetMaterial().GetColour();
    Vector ambient = color * 0.2f;

    ambient.x *= lightIntensity.gRed();
    ambient.y *= lightIntensity.gGreen();
    ambient.z *= lightIntensity.gBlue();

    //if (shadow) {
    //    color = ambient;
    //}

    Vector l = (position - IntersectionPoint).Normalize();

    Vector normal = Vector(1, 0, 0);

    float shade = normal.dotProduct(l);
    float attenaution = 1.0 / (constAtten + linearAtten * dist + quadAtten * (dist * dist));

    Vector R = l - (normal * normal.dotProduct(l) * 2.0f);
    float ss = -cameraDir.dotProduct(R);
    float sp = -cameraDir.dotProduct(R);
    float spec = 0;

    if (-ss > 0) {
        spec = pow(ss, closestObject->GetMaterial().specularAmount);
    }

    spec *= closestObject->GetMaterial().specularCoeff;

    shade = std::clamp(shade * attenaution, 0.2f, 1.0f);
    color.x *= shade * lightIntensity.gRed();
    color.y *= shade * lightIntensity.gGreen();
    color.z *= shade * lightIntensity.gBlue();

    Vector specular = color;
    specular.x *= spec * lightIntensity.gRed();
    specular.y *= spec * lightIntensity.gGreen();
    specular.z *= spec * lightIntensity.gBlue();

    color = color + specular;

    color.x = std::clamp(color.x, 0.0f, 255.0f);
    color.y = std::clamp(color.y, 0.0f, 255.0f);
    color.z = std::clamp(color.z, 0.0f, 255.0f);

    return color;
}
