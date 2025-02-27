#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

class Vector3D
{
public:
    double e[3];

    Vector3D();
    Vector3D(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    Vector3D operator-() const;
    double operator[](int i) const;
    double &operator[](int i);

    Vector3D &operator+=(const Vector3D &v);
    Vector3D &operator*=(double t);
    Vector3D &operator/=(double t);

    double length() const;
    double length_squared() const;
};

using Point3D = Vector3D;

std::ostream &operator<<(std::ostream &out, const Vector3D &v);
Vector3D operator+(const Vector3D &u, const Vector3D &v);
Vector3D operator-(const Vector3D &u, const Vector3D &v);
Vector3D operator*(const Vector3D &u, const Vector3D &v);
Vector3D operator*(double t, const Vector3D &v);
Vector3D operator*(const Vector3D &v, double t);
Vector3D operator/(const Vector3D &v, double t);
double dot(const Vector3D &u, const Vector3D &v);
Vector3D cross(const Vector3D &u, const Vector3D &v);
Vector3D unit_vector(const Vector3D &v);

#endif