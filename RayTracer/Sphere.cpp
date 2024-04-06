#include <cmath>
#include "Sphere.h"

#include <iostream>


Vector Sphere::GetIntersectionPoint()
{
    return intersectionPoint;
}

Vector Sphere::Intersect(Ray ray) {

    Vector oc = ray.Origin - Center;

    float temp1 = 0.0f;
    float temp2 = 0.0f;

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
        temp1 = (-b - std::sqrtf(discriminant)) / a;
        //std::cout << "t1 " << temp << std::endl;

        if (temp1 <= this->t_max && temp1 > this->t_min) {
            one = ray.Origin + ray.Direction * temp1;
            //std::cout << one << std::endl;

        }

        temp2 = (-b + std::sqrtf(discriminant)) / a;
        //std::cout << "t2 " << temp << std::endl;
        if (temp2 <= this->t_max && temp2 > this->t_min) {
            two = ray.Origin + ray.Direction * temp2;
            //std::cout << two << std::endl;

        }

        //std::cout << "LENGTHS: " << one.GetLength() << " " << two.GetLength() << std::endl;
        if (temp1 < temp2) {
           // std::cout << "one " << one.GetLength() << std::endl;
            //std::cout << "two " << two.GetLength() << std::endl;
            return Vector(temp1,temp1,temp1);
        }
        else {
            //std::cout << "one " << one << std::endl;
            //std::cout << "two " << two << std::endl;
            return Vector(temp2,temp2,temp2);
        }
    }

    if (discriminant <= 0.001f && discriminant >= -0.001f)
    {
        temp1 = (-b - std::sqrtf(discriminant)) / a;
        //std::cout << "temp1 " << temp << std::endl;

        if (temp1 <= this->t_max && temp1 > this->t_min) {
            one = ray.Origin + ray.Direction * temp1;

        }

        temp2 = (-b + std::sqrtf(discriminant)) / a;
        //std::cout << "temp2 " << temp << std::endl;

        if (temp2 <= this->t_max && temp2 > this->t_min) {

            two = ray.Origin + ray.Direction * temp2;

        }


        //std::cout << "LENGTHS: " << one.GetLength() << " " << two.GetLength() << std::endl;
        if (temp1 < temp2) {
            // std::cout << "one " << one.GetLength() << std::endl;
             //std::cout << "two " << two.GetLength() << std::endl;
            return Vector(temp1, temp1, temp1);
        }
        else {
            //std::cout << "one " << one << std::endl;
            //std::cout << "two " << two << std::endl;
            return Vector(temp2, temp2, temp2);
        }
    }
    //std::cout << "Nie ma przeciecia!" << std::endl;
    return Vector(-1000,-1000,-1000);
}
