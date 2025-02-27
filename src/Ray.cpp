#include "Ray.h"

ray::ray() {}

ray::ray(const Point3D &origin, const Vector3D &direction) : orig(origin), dir(direction) {}

const Point3D &ray::origin() const
{
    return orig;
}

const Vector3D &ray::direction() const
{
    return dir;
}

Point3D ray::at(double t) const
{
    return orig + t * dir;
}