#include "Color.h"
#include "Ray.h"
#include "Vector3D.h"

#include <iostream>
#include <fstream>
#include <cmath>

bool hit_sphere(const Point3D &center, double radius, const ray &r, double &t)
{
    Vector3D oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return false;
    }
    else
    {
        t = (-b - sqrt(discriminant)) / (2.0 * a);
        return true;
    }
}

Color ray_color(const ray &r, const Point3D &light_position, const Color &ambient_light, const Color &diffuse_light, const Color &sphere_color)
{
    double t;
    if (hit_sphere(Point3D(0, 0, -1), 0.5, r, t))
    {
        Point3D hit_point = r.origin() + t * r.direction();
        Vector3D normal = unit_vector(hit_point - Point3D(0, 0, -1));
        Vector3D light_direction = unit_vector(light_position - hit_point);

        Color ambient = ambient_light * sphere_color;

        double diffuse_intensity = std::max(0.0, dot(normal, light_direction));
        Color diffuse = diffuse_intensity * diffuse_light * sphere_color;

        Color final_color = ambient + diffuse;
        return final_color;
    }

    Vector3D unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 2160;

    int image_height = int(image_width / aspect_ratio);

    int num_frames = 10;

    for (int frame = 0; frame < num_frames; ++frame)
    {
        auto focal_length = 10.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * aspect_ratio;
        auto camera_center = Point3D(0, 0, 10);

        auto viewport_u = Vector3D(viewport_width, 0, 0);
        auto viewport_v = Vector3D(0, -viewport_height, 0);

        auto pixel_delta_u = viewport_u / image_width;
        auto pixel_delta_v = viewport_v / image_height;

        auto viewport_upper_left = camera_center - Vector3D(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u - pixel_delta_v);

        // Point3D light_position(5, 5, 5);
        double angle = 2 * M_PI * frame / num_frames;
        Point3D light_position(5 * cos(angle), 5 * sin(angle), 5);

        Color ambient_light(0.1, 0.1, 0.1);
        Color diffuse_light(0.8, 0.8, 0.8);

        Color sphere_color(0.0, 1, 0.0);

        std::string filename = "frame_" + std::to_string(frame) + ".ppm";
        std::ofstream out(filename);

        out << "P3\n"
            << image_width << " " << image_height << "\n255\n";
        // std::cout << "P3\n"
        //           << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++)
        {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++)
            {
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                ray r(camera_center, pixel_center - camera_center);

                Color pixel_color = ray_color(r, light_position, ambient_light, diffuse_light, sphere_color);
                write_color(out, pixel_color);
            }
        }

        out.close();
    }

    std::clog << "\rDone.                 \n";
}