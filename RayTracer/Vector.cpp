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

float Vector::GetLength() const {
    return (float)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void Vector::Normalize() {
    float len = GetLength();

    if (len != 0)
        this->operator/(len);
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
