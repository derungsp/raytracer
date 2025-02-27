#ifndef COLOR_H
#define COLOR_H

#include "Vector3D.h"
#include <iostream>

using Color = Vector3D;

void write_color(std::ostream &out, const Color &pixel_color);

#endif