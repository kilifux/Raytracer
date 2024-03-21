#include "Ray.h"

Ray::Ray()
{
    this->Origin = Vector(0, 0, 0);
    this->Direction = Vector(0, 0, -1);
}

Ray Ray::GetTwoPointsRay(const Vector& A, const Vector& B)
{
    Vector foundVector = B - A;
    return { foundVector.Normalize(), A };
}
