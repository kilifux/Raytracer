#include <cmath>
#include "Sphere.h"

#include <iostream>


Vector Sphere::GetIntersectionPoint()
{
    return intersectionPoint;
}

Vector Sphere::Intersect(Ray ray) {

    Vector oc = ray.Origin - Center;

    float temp = 0.0f;

    float a = ray.Direction.dotProduct(ray.Direction);
    float b = oc.dotProduct(ray.Direction);
    //std::cout <<"ray " << ray.Direction << std::endl;
    float c = oc.dotProduct(oc) - Radius * Radius;

    float discriminant = b * b - a * c;
    //std::cout << discriminant << std::endl;
    Vector one = Vector(-1000, -1000, -1000);
    Vector two = Vector(-1000, -1000, -1000);

    if (discriminant > 0.001f)
    {
        temp = (-b - std::sqrtf(discriminant)) / a;
        //std::cout << "t1 " << temp << std::endl;

        if (temp <= this->t_max && temp > this->t_min) {
            one = ray.Origin + ray.Direction * temp;
            //std::cout << one << std::endl;

        }

        temp = (-b + std::sqrtf(discriminant)) / a;
        //std::cout << "t2 " << temp << std::endl;
        if (temp <= this->t_max && temp > this->t_min) {
            two = ray.Origin + ray.Direction * temp;
            //std::cout << two << std::endl;

        }

        if (one.z > two.z) {
            //std::cout << "one " << one << std::endl;
            return one;
        }
        else {
            //std::cout << "two " << two << std::endl;
            return two;
        }
    }

    if (discriminant <= 0.001f && discriminant >= -0.001f)
    {
        temp = (-b - std::sqrtf(discriminant)) / a;
        //std::cout << "temp1 " << temp << std::endl;

        if (temp <= this->t_max && temp > this->t_min) {
            one = ray.Origin + ray.Direction * temp;

        }

        temp = (-b + std::sqrtf(discriminant)) / a;
        //std::cout << "temp2 " << temp << std::endl;

        if (temp <= this->t_max && temp > this->t_min) {

            two = ray.Origin + ray.Direction * temp;

        }


        //std::cout << one << " " << two << std::endl;
        if (one.z > two.z) {
            //std::cout << "one " << one << std::endl;
            return one;
        }
        else {
            //std::cout << "two " << two << std::endl;
            return two;
        }
    }
    //std::cout << "Nie ma przeciecia!" << std::endl;
    return Vector(-1000,-1000,-1000);
}
