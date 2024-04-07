#include "PointLight.h"
#include <algorithm>


Vector PointLight::calculateLightingColor(std::vector<std::shared_ptr<Object>> objects, Vector IntersectionPoint, std::shared_ptr<Object> closestObject, Vector cameraDir)
{
    bool shadow = false;
    float dist = (position - IntersectionPoint).GetLength();

    Ray nRay = Ray(position, (IntersectionPoint - position).Normalize());

    for (int i = 0; i < objects.size(); i++) {
        std::shared_ptr<Object> s = objects[i];
        Vector res = s->Intersect(nRay);

        if (dist - res.GetLength() > 0.1f)
        {
            shadow = true;
            break;
        }
    }

    Vector color = closestObject->GetMaterial().GetColour() * intensity;
    Vector ambient = color * 0.2f;

    ambient.x *= lightIntensity.gRed();
    ambient.y *= lightIntensity.gGreen();
    ambient.z *= lightIntensity.gBlue();

    if (shadow) {
        color = ambient;
    } 
    else
    {
        float attenuation = 1.0 / (constAtten + linearAtten * dist + quadAtten * (dist * dist));

        // Obliczanie kierunku œwiat³a i normalizacja
        Vector lightDir = (position - IntersectionPoint).Normalize();

        // Obliczanie stopnia oœwietlenia (cosinus k¹ta miêdzy normaln¹ powierzchni a kierunkiem œwiat³a)
        float shade = closestObject->GetNormalAt(IntersectionPoint).dotProduct(lightDir);

        // Obliczanie odbicia zwierciadlanego
        Vector R = lightDir - closestObject->GetNormalAt(IntersectionPoint) * 2.0f * closestObject->GetNormalAt(IntersectionPoint).dotProduct(lightDir);

        // Obliczanie sk³adnika odbicia zwierciadlanego
        float spec = std::pow(std::max(cameraDir.dotProduct(R), 0.0f), closestObject->GetMaterial().specularAmount);

        // Obliczanie sk³adnika odbicia œwiat³a
        Vector lightIntensityVector = Vector{ (float)lightIntensity.gRed(), (float)lightIntensity.gGreen() ,(float)lightIntensity.gBlue()};

        Vector diffuse = color * shade * attenuation;

        diffuse.x *= lightIntensityVector.x;
        diffuse.y *= lightIntensityVector.y;
        diffuse.z *= lightIntensityVector.z;

        Vector specular = color;
        specular.x *= spec * lightIntensityVector.x;
        specular.y *= spec * lightIntensityVector.y;
        specular.z *= spec * lightIntensityVector.z;

        // £¹czenie sk³adowych koloru
        color = diffuse + specular;
    }

    color.x = std::clamp(color.x, 0.0f, 1.0f);
    color.y = std::clamp(color.y, 0.0f, 1.0f);
    color.z = std::clamp(color.z, 0.0f, 1.0f);

    return color;


}
