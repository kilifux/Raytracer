#include "Ray.h"

Ray Ray::GetTwoPointsRay(const Vector& A, const Vector& B)
{
    Vector foundVector = B - A;
    return { foundVector.Normalize(), A };
}
