#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D
{
public:
    double x, y;

    Vector2D(double x = 0, double y = 0);

    Vector2D operator+(const Vector2D &other) const;
    Vector2D operator-(const Vector2D &other) const;
    Vector2D operator*(double scalar) const;

    friend std::ostream &operator<<(std::ostream &os, const Vector2D &v)
    {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

#endif