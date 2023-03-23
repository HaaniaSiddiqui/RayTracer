#include <iostream>
#include <sstream>
#include "Ray.hpp"

Ray::Ray() : o(0), d(0), w(1) {}
Ray::Ray(const Point3D &origin, const Vector3D &dir) : o(origin), d(dir), w(1) {}

std::string Ray::to_string() const
{
    std::stringstream stream;
    stream << "Origin -> (" << o.x << "," << o.y << "," << o.z << ")" << std::endl;
    stream << "Direction -> (" << d.x << "," << d.y << "," << d.z << ")" << std::endl;
    return stream.str();
}
