#include <cmath>
#include "Sphere.h"

#include <iostream>

bool Sphere::Intersect(Ray ray, float t_min, float t_max) const {

    Vector oc = ray.Origin - Center;

    float temp = 0.0f;

    float a = ray.Direction.dotProduct(ray.Direction);
    float b = oc.dotProduct(ray.Direction);
    //std::cout <<"ray " << ray.Direction << std::endl;
    float c = oc.dotProduct(oc) - Radius * Radius;

    float discriminant = b * b - a * c;
    //std::cout << discriminant << std::endl;

    if (discriminant > 0.00001f)
    {
        temp = (-b - std::sqrtf(discriminant)) / a;
        //std::cout << ray.pointAtParameter(temp) << std::endl;

        if (temp < t_max && temp > t_min)
            return true;

        temp = (-b + std::sqrtf(discriminant)) / a;

        if (temp < t_max && temp > t_min)
            return true;
    }

    if (discriminant < 0.00001f && discriminant > -0.00001f)
    {
        temp = (-b - std::sqrtf(discriminant)) / a;
        //std::cout << "temp1 " << temp << std::endl;

        if (temp <= t_max && temp > t_min) {
            //std::cout << ray.pointAtParameter(temp) << std::endl;

            return true;
        }

        temp = (-b + std::sqrtf(discriminant)) / a;
        //std::cout << "temp2 " << temp << std::endl;

        if (temp <= t_max && temp > t_min) {
            //std::cout << ray.pointAtParameter(temp) << std::endl;

            return true;
        }
    }
    //std::cout << "Nie ma przeciecia!" << std::endl;
    return false;
}
