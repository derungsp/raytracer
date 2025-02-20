#include "Vector2D.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <cmath>
#include <vector>

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

bool intersectsCircle(Vector2D rayOrigin, Vector2D rayDir, Vector2D circleCenter, double radius)
{
    Vector2D oc = rayOrigin - circleCenter;
    double a = rayDir.x * rayDir.x + rayDir.y * rayDir.y;
    double b = 2.0 * (oc.x * rayDir.x + oc.y * rayDir.y);
    double c = oc.x * oc.x + oc.y * oc.y - radius * radius;
    double discriminant = b * b - 4 * a * c;
    return discriminant >= 0;
}

int main()
{
    const int width = 1600;
    const int height = 1000;
    const Vector2D circleCenter(width / 2, height / 2);
    const double radius = 100.0;

    std::vector<Vector2D> rayOrigins;
    std::vector<Vector2D> rayDirs;

    rayOrigins.push_back(Vector2D(0, height / 2));
    rayDirs.push_back(Vector2D(1, 0));

    rayOrigins.push_back(Vector2D(0, height / 4));
    rayDirs.push_back(Vector2D(1, 0));

    rayOrigins.push_back(Vector2D(0, 3 * height / 4));
    rayDirs.push_back(Vector2D(1, 0));

    for (double x = 0.0; x < 10.0; x += 0.1)
    {
        rayOrigins.push_back(Vector2D(0, 0));
        rayDirs.push_back(Vector2D(x, 1));
    }

    std::string filename = getTimestampedFilename();
    std::ofstream image(filename);
    image << "P3\n"
          << width << " " << height << "\n255\n";

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Vector2D currentPoint(x, y);
            bool isRay = false;
            bool isIntersecting = false;

            for (size_t i = 0; i < rayOrigins.size(); ++i)
            {
                bool onRay = (x >= (int)rayOrigins[i].x && y == (int)(rayOrigins[i].y + (x - rayOrigins[i].x) * rayDirs[i].y / rayDirs[i].x));
                bool intersects = intersectsCircle(rayOrigins[i], rayDirs[i], circleCenter, radius);

                if (onRay)
                {
                    isRay = true;
                    if (intersects)
                    {
                        isIntersecting = true;
                        break;
                    }
                }
            }

            if (isRay && isIntersecting)
            {
                image << "0 255 0\n";
            }
            else if (isRay && !isIntersecting)
            {
                image << "0 0 255\n";
            }
            else if ((x - circleCenter.x) * (x - circleCenter.x) + (y - circleCenter.y) * (y - circleCenter.y) <= radius * radius)
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
    std::cout << "Image saved as " << filename << "\n";
    return 0;
}