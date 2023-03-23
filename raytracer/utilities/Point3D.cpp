#include <iostream>
#include "Point3D.hpp"
#include <cmath>
#include <sstream>
#include "Vector3D.hpp"


Point3D::Point3D():x(0), y(0), z(0) {}
Point3D::Point3D(double c):x(c), y(c), z(c) {}
Point3D::Point3D(double x, double y, double z): x(x), y(y), z(z) {}

std::string Point3D::to_string() const
{
    std::stringstream stream;
    stream << "Point -> (" << x << "," << y << "," << z << ")" << std::endl;
    return stream.str();
}

Point3D Point3D::operator-() const
{
    Point3D p(-x, -y, -z);
    return p;
}


Vector3D Point3D::operator-(const Point3D &p) const
{
    return Vector3D(x - p.x, y - p.y, z - p.z);
}

Point3D Point3D::operator+(const Vector3D& v) const
{
    return Point3D(x + v.x, y + v.y, z + v.z);
}

Point3D Point3D::operator-(const Vector3D& v) const
{
    return Point3D(x - v.x, y - v.y, z - v.z);
}

Point3D Point3D::operator*(const float s) const
{
    return Point3D(x * s, y * s, z * s);
}

float Point3D::d_squared(const Point3D& p) const
{
    float a, b, c;
    a = std::pow((x - p.x), 2);
    b = std::pow((y - p.y), 2);
    c = std::pow((z - p.z), 2);
    return a + b + c;
}

float Point3D::distance(const Point3D& p) const
{
    float sqr_dist = Point3D::d_squared(p);
    return std::sqrt(sqr_dist);
}

Point3D operator*(const float a, const Point3D& pt)
{
    return Point3D(a*pt.x, a*pt.y, a*pt.z);
}

Point3D min(const Point3D& a, const Point3D& b)
{
    return Point3D(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Point3D max(const Point3D& a, const Point3D& b)
{
    return Point3D(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}


Point3D Point3D::interpolate(const Point3D& p, const Point3D& q,
                             const Point3D& r, const Point3D& x,
                             const Point3D& y) {
  return Point3D(x.x + (r.x - p.x) / (q.x - p.x) * (y.x - x.x),
                 x.y + (r.y - p.y) / (q.y - p.y) * (y.y - x.y),
                 x.z + (r.z - p.z) / (q.z - p.z) * (y.z - x.z));
}


