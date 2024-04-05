#include "PointLight.h"


Vector PointLight::calculateLightingColor(std::vector<std::shared_ptr<Object>> objects, Vector IntersectionPoint, std::shared_ptr<Object> closestObject, Vector cameraDir)
{
    // Kierunek �wiat�a
    Vector lightDir = (position - IntersectionPoint).Normalize();

    // Kierunek normalny w punkcie przeci�cia
    Vector normal = Vector{ 1.f, 0.f, 0.f };    //closestObject->GetNormal(IntersectionPoint).Normalize();

    // Kierunek widzenia
    Vector viewDir = (cameraDir * -1).Normalize();

    // Obliczanie diffuse
    float diffuseIntensity = std::max(0.0f, normal.dotProduct(lightDir));
    Vector diffuseColor = closestObject->GetMaterial().GetColour() * diffuseIntensity;

    // Obliczanie specular
    Vector reflectDir = (lightDir - normal * (2 * lightDir.dotProduct(normal))).Normalize();
    float specularIntensity = pow(std::max(0.0f, reflectDir.dotProduct(viewDir)), closestObject->GetMaterial().specularAmount);

    Vector LightIntensityVector = Vector{ (float)lightIntensity.gRed(), (float)lightIntensity.gGreen() , (float)lightIntensity.gBlue() };
    Vector mulTemp = LightIntensityVector * specularIntensity;

   Vector specularColor = mulTemp * closestObject->GetMaterial().specularCoeff;

    // Sprawdzenie cienia
    bool shadow = isInShadow(objects, IntersectionPoint);

    // Je�li punkt przeci�cia znajduje si� w cieniu, zwracamy kolor t�a
    if (shadow) {
        return Vector(0.0f, 0.2f, 0.0f);
    }

    // Kolor ostateczny to suma diffuse i specular
    Vector finalColor = diffuseColor * intensity + specularColor * intensity;

    return finalColor;
}

bool PointLight::isInShadow(std::vector<std::shared_ptr<Object>> objects, Vector intersectionPoint)
{
    // Sprawdzenie, czy punkt przeci�cia znajduje si� w cieniu
    for (auto& obj : objects) {
        Vector dist = obj->Intersect(Ray(intersectionPoint, position));
        if (dist.z > 0 && dist.GetLength() < (position - intersectionPoint).GetLength()) {
            return true; // Punkt przeci�cia jest w cieniu
        }
    }
    return false; // Punkt przeci�cia nie jest w cieniu
}
