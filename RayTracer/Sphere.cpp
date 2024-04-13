#include <cmath>
#include "Sphere.h"

#include <iostream>


Vector Sphere::GetIntersectionPoint()
{
    return intersectionPoint;
}

Vector Sphere::GetIntersectionNormal() {
    //intersectionNormal = intersectionNormal.Normalize();
    return intersectionNormal;
}

Vector Sphere::Intersect(Ray ray) {

    Vector oc = ray.Origin - Center;

    float temp1 = 0.0f;
    float temp2 = 0.0f;

    float a = ray.Direction.dotProduct(ray.Direction);
    float b = oc.dotProduct(ray.Direction);

    float c = oc.dotProduct(oc) - Radius * Radius;

    float discriminant = b * b - a * c;

    Vector one = Vector(-1000, -1000, -1000);
    Vector two = Vector(-1000, -1000, -1000);
    intersectionPoint = Vector();
    intersectionNormal = Vector();

    if (discriminant > 0.001f)
    {
        temp1 = (-b - std::sqrtf(discriminant)) / a;


        if (temp1 <= this->t_max && temp1 > this->t_min) {
            one = ray.Origin + ray.Direction * temp1;


        }

        temp2 = (-b + std::sqrtf(discriminant)) / a;

        if (temp2 <= this->t_max && temp2 > this->t_min) {
            two = ray.Origin + ray.Direction * temp2;


        }

        if (temp1 < temp2) {
            intersectionPoint = one;
            intersectionNormal = (intersectionPoint - Center).Normalize();
            return Vector(temp1, temp1, temp1);
        }
        else {
            intersectionPoint = two;
            intersectionNormal = (intersectionPoint - Center).Normalize();
            return Vector(temp2, temp2, temp2);
        }
    }

    if (discriminant <= 0.001f && discriminant >= -0.001f)
    {
        temp1 = (-b - std::sqrtf(discriminant)) / a;


        if (temp1 <= this->t_max && temp1 > this->t_min) {
            one = ray.Origin + ray.Direction * temp1;

        }

        temp2 = (-b + std::sqrtf(discriminant)) / a;


        if (temp2 <= this->t_max && temp2 > this->t_min) {

            two = ray.Origin + ray.Direction * temp2;

        }



        if (temp1 < temp2) {
            intersectionPoint = one;
            intersectionNormal = (intersectionPoint - Center).Normalize();
            return Vector(temp1, temp1, temp1);
        }
        else {
            intersectionPoint = two;
            intersectionNormal = (intersectionPoint - Center).Normalize();
            return Vector(temp2, temp2, temp2);
        }
    }

    return Vector(-1000,-1000,-1000);
}
