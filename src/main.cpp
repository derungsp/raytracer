#include "Vector2D.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <cmath>

std::string getTimestampedFilename()
{
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);

    std::ostringstream filename;
    filename << "out/image_"
             << (localTime->tm_year + 1900) << "-"
             << (localTime->tm_mon + 1) << "-"
             << localTime->tm_mday << "_"
             << localTime->tm_hour << "-"
             << localTime->tm_min << "-"
             << localTime->tm_sec
             << ".ppm";

    return filename.str();
}

bool isInCircle(int x, int y, int cx, int cy, int r)
{
    int dx = x - cx;
    int dy = y - cy;
    return (dx * dx + dy * dy) <= (r * r);
}

int main()
{
    const int width = 800;
    const int height = 500;

    const int midX = width - (width / 2);
    const int midY = height - (height / 2);
    const int radius = 100;

    std::string filename = getTimestampedFilename();
    std::ofstream image(filename);
    image << "P3\n"
          << width << " " << height << "\n255\n";

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (isInCircle(x, y, midX, midY, radius))
            {
                image << "255 0 0\n";
            }
            else
            {
                image << "255 255 255\n";
            }
        }
    }

    image.close();
    std::cout << "image saved as image.ppm\n";
    return 0;
}
