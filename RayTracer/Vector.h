#pragma once

class Vector {
public:
    float x, y, z;


    Vector();
    Vector(float x, float y, float z);
    Vector(const Vector& vector);
    ~Vector();

    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(float f) const;
    Vector operator/(float f) const;

    float GetLength() const;
    void Normalize();
    float dotProduct(Vector v);
    Vector cross(Vector v);


};
