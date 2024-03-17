#pragma once
#include <ostream>
#include <iostream>

class Vector {
public:
    float x, y, z;


    Vector();
    Vector(float x, float y, float z);
    Vector(const Vector& vector);
    ~Vector();

    Vector operator-() const;

    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(float f) const;
    Vector operator/(float f) const;

    friend std::ostream& operator<<(std::ostream& Os, const Vector& vector3);



    float getAngle(const Vector& vector);
    float GetLength() const;
    Vector Normalize();
    float dotProduct(Vector v);
    Vector cross(Vector v);


};
