#ifndef RAY_H
#define RAY_H

#include "Vector3D.h"

class ray
{
public:
    ray();
    ray(const Point3D &origin, const Vector3D &direction);

    const Point3D &origin() const;
    const Vector3D &direction() const;
    Point3D at(double t) const;

private:
    Point3D orig;
    Vector3D dir;
};

#endif