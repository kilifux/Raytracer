#include "Vector.h"

#include <cmath>

Vector::Vector() {

}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {

}

Vector::Vector(const Vector& vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
}

Vector::~Vector() {

}

Vector Vector::operator-() const
{
    return { -this->x, -this->y, -this->z };
}

Vector Vector::operator+(const Vector& v) const {
    return { x + v.x, y + v.y, z + v.z };
}

Vector Vector::operator-(const Vector& v) const {
    return { x - v.x, y - v.y, z - v.z };
}

Vector Vector::operator*(float f) const {
    return { x * f, y * f, z * f };
}

Vector Vector::operator/(float f) const {
    return { x / f, y / f, z / f };
}

float Vector::getAngle(const Vector& vector) 
{
    return acos(dotProduct(vector) / (this->GetLength() * vector.GetLength())); 
}

float Vector::GetLength() const {
    return (float)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vector Vector::Normalize() {
    float len = GetLength();

    if (len < 0 )
        return Vector(0, 0, 0);

    return *this/len;
}

float Vector::dotProduct(Vector v) {
    Vector result;
    result.x = x * v.x;
    result.y = y * v.y;
    result.z = z * v.z;

    return result.x + result.y + result.z;
}

Vector Vector::cross(Vector v) {
    return Vector(y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x);
}


std::ostream& operator<<(std::ostream& Os, const Vector& vector3)
{
    Os << "[" << vector3.x << "," << vector3.y << "," << vector3.z << "]";
    return Os;
}