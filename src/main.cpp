#include "Color.h"
#include "Ray.h"
#include "Vector3D.h"

#include <iostream>

bool hit_sphere(const Point3D &center, double radius, const ray &r)
{
    Vector3D oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}

Color ray_color(const ray &r)
{
    Color accumulated_color(0, 0, 0);

    if (hit_sphere(Point3D(-0.25, -0.25, -1), 0.5, r))
        accumulated_color += Color(1, 0, 0);
    if (hit_sphere(Point3D(0.25, -0.25, -1), 0.5, r))
        accumulated_color += Color(0, 1, 0);
    if (hit_sphere(Point3D(0, 0.25, -1), 0.5, r))
        accumulated_color += Color(0, 0, 1);

    if (accumulated_color.x() > 0 || accumulated_color.y() > 0 || accumulated_color.z() > 0)
        return accumulated_color;

    Vector3D unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main()
{
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 2160;

    int image_height = int(image_width / aspect_ratio);

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * aspect_ratio;
    // auto camera_center = Point3D(0, 0, 0);
    auto camera_center = Point3D(0, 0, 1);

    auto viewport_u = Vector3D(viewport_width, 0, 0);
    auto viewport_v = Vector3D(0, -viewport_height, 0);

    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = camera_center - Vector3D(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u - pixel_delta_v);

    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            ray r(camera_center, pixel_center - camera_center);

            Color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}