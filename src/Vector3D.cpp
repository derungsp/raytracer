#include "Vector3D.h"
#include <cmath>

Vector3D::Vector3D() : e() {}
Vector3D::Vector3D(double e0, double e1, double e2) : e()
{
    e[0] = e0;
    e[1] = e1;
    e[2] = e2;
}

double Vector3D::x() const { return e[0]; }
double Vector3D::y() const { return e[1]; }
double Vector3D::z() const { return e[2]; }

Vector3D Vector3D::operator-() const { return Vector3D(-e[0], -e[1], -e[2]); }
double Vector3D::operator[](int i) const { return e[i]; }
double &Vector3D::operator[](int i) { return e[i]; }

Vector3D &Vector3D::operator+=(const Vector3D &v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

Vector3D &Vector3D::operator*=(double t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

Vector3D &Vector3D::operator/=(double t)
{
    return *this *= 1 / t;
}

double Vector3D::length() const
{
    return std::sqrt(length_squared());
}

double Vector3D::length_squared() const
{
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

std::ostream &operator<<(std::ostream &out, const Vector3D &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

Vector3D operator+(const Vector3D &u, const Vector3D &v)
{
    return Vector3D(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

Vector3D operator-(const Vector3D &u, const Vector3D &v)
{
    return Vector3D(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

Vector3D operator*(const Vector3D &u, const Vector3D &v)
{
    return Vector3D(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

Vector3D operator*(double t, const Vector3D &v)
{
    return Vector3D(t * v.e[0], t * v.e[1], t * v.e[2]);
}

Vector3D operator*(const Vector3D &v, double t)
{
    return t * v;
}

Vector3D operator/(const Vector3D &v, double t)
{
    return (1 / t) * v;
}

double dot(const Vector3D &u, const Vector3D &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

Vector3D cross(const Vector3D &u, const Vector3D &v)
{
    return Vector3D(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                    u.e[2] * v.e[0] - u.e[0] * v.e[2],
                    u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

Vector3D unit_vector(const Vector3D &v)
{
    return v / v.length();
}