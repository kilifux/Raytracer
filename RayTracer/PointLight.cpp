#include "PointLight.h"
#include <algorithm> 

Vector PointLight::calculateLightingColor(std::vector<std::shared_ptr<Object>> objects, Vector IntersectionPoint, std::shared_ptr<Object> closestObject, Vector cameraDir, int nr)
{


    bool inShadow = false;
    Ray ray = Ray(position, (IntersectionPoint - position).Normalize());
    //float dist = (position - IntersectionPoint).GetLength();

    float closestDistance = 1000;
    int closestNumber = nr;
    Vector distance = Vector(-1000, -1000, -1000);

    for (int i = 0; i < objects.size(); i++) {

        std::shared_ptr<Object> obj = objects[i];
        distance = obj->Intersect(ray);

        if (distance.z != -1000 && distance.z < 19.0f && distance.z > 0.1f) {

            if (distance.z < closestDistance) {
                closestDistance = distance.z;
                closestNumber = i;
            }

        }
    }

    if (closestNumber != nr) {
        inShadow = true;
    } else if (closestNumber == nr && closestDistance != -1000 && closestDistance > 19.0f) {
        inShadow = true;
    }
    
    Vector color = closestObject->GetMaterial().GetColour();
    Vector ambient = color * 0.2f;

    ambient.x *= lightIntensity.gRed();
    ambient.y *= lightIntensity.gGreen();
    ambient.z *= lightIntensity.gBlue();

    if (inShadow) {
        color = ambient;
    }
    else {
        //Vector color = closestObject->GetMaterial().GetColour();
        
        //phong
        Vector lightDir = (position - IntersectionPoint).Normalize();

        Vector normal = closestObject->GetIntersectionNormal();

        float shade = normal.dotProduct(lightDir);
        float attenuation = 1.0 / (constAtten + linearAtten * closestDistance + quadAtten * (closestDistance * closestDistance));


        Vector R = lightDir - (normal * normal.dotProduct(lightDir) * 2.0f);
        float ss = -cameraDir.dotProduct(R);
        float spec = 0;

        if (-ss > 0) {
            spec = pow(ss, closestObject->GetMaterial().specularAmount);
        }

        spec *= closestObject->GetMaterial().specularCoeff;

        shade = std::clamp(shade * attenuation, 0.2f, 1.0f);
        color.x *= shade * lightIntensity.gRed();
        color.y *= shade * lightIntensity.gGreen();
        color.z *= shade * lightIntensity.gBlue();

        Vector specular = color;
        specular.x *= spec * lightIntensity.gRed();
        specular.y *= spec * lightIntensity.gGreen();
        specular.z *= spec * lightIntensity.gBlue();

        color = color + specular;
        
    }
    color.x = std::clamp(color.x, 0.0f, 1.0f);
    color.y = std::clamp(color.y, 0.0f, 1.0f);
    color.z = std::clamp(color.z, 0.0f, 1.0f);

    return color;
    
}
