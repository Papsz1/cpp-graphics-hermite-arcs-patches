#include "HCoordinates3.h"

using namespace cagd;

GLfloat HCoordinate3::operator *(const HCoordinate3& rhs) const
{
    GLfloat wd = w() * rhs.w();
    GLfloat res = (x() * rhs.x()) / wd +
            (y() * rhs.y()) / wd +
            (z() * rhs.z()) / wd;

    return res;
}


// homework: cross product
const HCoordinate3 HCoordinate3::operator ^(const HCoordinate3& rhs) const
{
    return HCoordinate3(
                y() * rhs.z() - z() * rhs.y(),
                z() * rhs.x() - x() * rhs.z(),
                x() * rhs.y() - y() * rhs.x(),
                w() * rhs.w()
                );
}

HCoordinate3& HCoordinate3::operator ^=(const HCoordinate3& rhs)
{
    GLfloat xtemp = y() * rhs.z() - z() * rhs.y();
    GLfloat ytemp = z() * rhs.x() - x() * rhs.z();

    z() = x() * rhs.y() - y() * rhs.x();
    w() = w() * rhs.w();

    x() = xtemp;
    y() = ytemp;

    return *this;
}

const HCoordinate3 HCoordinate3::operator *(GLfloat rhs) const
{
    return HCoordinate3(x() * rhs, y() * rhs, z() * rhs, w());
}

HCoordinate3& HCoordinate3::operator *=(GLfloat rhs)
{
    x() *= rhs;
    y() *= rhs;
    z() *= rhs;

    return *this;
}

inline const HCoordinate3 HCoordinate3::operator /(GLfloat rhs) const
{
    return HCoordinate3(x(), y(), z(), w()*rhs);
};

// divide this with a scalar
inline HCoordinate3& HCoordinate3::operator /=(GLfloat rhs)
{
    w() *= rhs;

    return *this;
}

// length of vector represented by this homogeneous coordinate
inline GLfloat HCoordinate3::length() const
{
    return sqrt((*this) * (*this));
}

// normalize
inline HCoordinate3& HCoordinate3::normalize()
{
    GLfloat l = length();

    if (l && l != 1.0)
        *this /= l;

    return *this;
}

// homework: get components by value
inline GLfloat HCoordinate3::operator[](GLuint rhs) const
{
    return _data[rhs];
}

inline GLfloat HCoordinate3::x() const
{
    return _data[0];
}

inline GLfloat HCoordinate3::y() const
{
    return _data[1];
}

inline GLfloat HCoordinate3::z() const
{
    return _data[2];
}

inline GLfloat HCoordinate3::w() const
{
    return _data[3];
}

inline GLfloat& HCoordinate3::operator[](GLuint rhs)
{
    return _data[rhs];
}

inline GLfloat& HCoordinate3::x()
{
    return _data[0];
}

inline GLfloat& HCoordinate3::y()
{
    return _data[1];
}

inline GLfloat& HCoordinate3::z()
{
    return _data[2];
}

inline GLfloat& HCoordinate3::w()
{
    return _data[3];
}
