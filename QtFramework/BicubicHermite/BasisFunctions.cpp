#include <cmath>
#include "BasisFunctions.h"

using namespace std;
using namespace cagd;

// zeroth-order derivatives
GLdouble BicubicHermiteBasisFunctions::F0(GLdouble u)
{
    return (2.0 * pow(u, 3) - 3.0 * pow(u, 2) + 1);
}

GLdouble BicubicHermiteBasisFunctions::F1(GLdouble u)
{
    return (-2.0 * pow(u, 3) + 3.0 * pow(u, 2));
}

GLdouble BicubicHermiteBasisFunctions::F2(GLdouble u)
{
    return (pow(u, 3) - 2.0 * pow(u, 2) + u);
}

GLdouble BicubicHermiteBasisFunctions::F3(GLdouble u)
{
    return (pow(u, 3) - pow(u, 2));
}

// first-order derivatives
GLdouble BicubicHermiteBasisFunctions::d1F0(GLdouble u)
{
    return (6.0 * u * (u - 1.0));
}

GLdouble BicubicHermiteBasisFunctions::d1F1(GLdouble u)
{
    return (-6.0 * u * (u - 1.0));
}

GLdouble BicubicHermiteBasisFunctions::d1F2(GLdouble u)
{
    return (3.0 * pow(u, 2) - 4.0 * u + 1.0);
}

GLdouble BicubicHermiteBasisFunctions::d1F3(GLdouble u)
{
    return (u * (3.0 * u - 2));
}

// second-order derivatives
GLdouble BicubicHermiteBasisFunctions::d2F0(GLdouble u)
{
    return (12.0 * u - 6.0);
}

GLdouble BicubicHermiteBasisFunctions::d2F1(GLdouble u)
{
    return (6.0 - 12.0 * u);
}

GLdouble BicubicHermiteBasisFunctions::d2F2(GLdouble u)
{
    return (6.0 * u - 4.0);
}

GLdouble BicubicHermiteBasisFunctions::d2F3(GLdouble u)
{
    return (6.0 * u - 2.0);
}

DCoordinate3 BicubicHermiteBasisFunctions::direction(GLdouble radius, GLdouble u, GLdouble v)
{ 
    return DCoordinate3(radius * sin(u) * cos(v), radius * sin(u) * sin(v), radius * cos(u)); 
}