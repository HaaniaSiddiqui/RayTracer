#include <iostream>
#include <sstream>
#include <cmath>
#include "Triangle.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Constants.hpp"

Triangle::Triangle(): v0(0), v1(0), v2(0) {}
Triangle::Triangle(const Point3D& p0, const Point3D& p1, const Point3D& p2): v0(p0), v1(p1), v2(p2) {}
Triangle::Triangle(const Triangle& object): v0(object.v0), v1(object.v1), v2(object.v2) {}

Triangle& Triangle::operator=(const Triangle& rhs)
{
    this->v0 = rhs.v0;
    this->v1 = rhs.v1;
    this->v2 = rhs.v2;
    return *this;
}

std::string Triangle::to_string() const
{
    std::stringstream stream;
    stream << "v0 -> (" << v0.x << ", " << v0.y << ", " << v0.z << ")" << std::endl;
    stream << "v1 -> (" << v1.x << ", " << v1.y << ", " << v1.z << ")" << std::endl;
    stream << "v2 -> (" << v2.x << ", " << v2.y << ", " << v2.z << ")" << std::endl;
    return stream.str();
}

bool Triangle::hit(const Ray& ray, double& t, ShadeInfo& s) const
{
    // Reference - Ray Tracing from the ground up

    double a = this->v0.x - this->v1.x, b = this->v0.x - this->v2.x, c = ray.d.x, d = this->v0.x - ray.o.x;
    double e = this->v0.y - this->v1.y, f = this->v0.y - this->v2.y, g = ray.d.y, h = this->v0.y - ray.o.y;
    double i = this->v0.z - this->v1.z, j = this->v0.z - this->v2.z, k = ray.d.z, l = this->v0.z - ray.o.z;

    double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
    double q = g * i - e * k, ss = e * j - f * i;

    double inv_denom = 1.0 / (a * m + b * q + c * ss);

    double e1 = d * m - b * n - c * p;
    double beta = e1 * inv_denom;

    if (beta < 0.0) return false;

    double r = e * l - h * i;
    double e2 = a * n + d * q + c * r;
    double gamma = e2 * inv_denom;

    if (gamma < 0.0) return false;

    if (beta + gamma > 1.0) return false;

    double e3 = a * p - b * r + d * ss;
    double t_value = e3 * inv_denom;

	if (t_value < kEpsilon) return false;

    Vector3D normal = (this->v0 - this->v1) ^ (this->v0 - this->v2);
    normal.normalize();

    t = t_value;
    s.ray = ray;
    s.t = t;
    s.normal = normal;
    s.hit_point = ray.o + (t * ray.d);

    return true;
}

bool Triangle::shadow_hit(const Ray& ray, float& t) const
{
    double a = this->v0.x - this->v1.x, b = this->v0.x - this->v2.x, c = ray.d.x, d = this->v0.x - ray.o.x;
    double e = this->v0.y - this->v1.y, f = this->v0.y - this->v2.y, g = ray.d.y, h = this->v0.y - ray.o.y;
    double i = this->v0.z - this->v1.z, j = this->v0.z - this->v2.z, k = ray.d.z, l = this->v0.z - ray.o.z;

    double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
    double q = g * i - e * k, ss = e * j - f * i;

    double inv_denom = 1.0 / (a * m + b * q + c * ss);

    double e1 = d * m - b * n - c * p;
    double beta = e1 * inv_denom;

    if (beta < 0.0) return false;

    double r = e * l - h * i;
    double e2 = a * n + d * q + c * r;
    double gamma = e2 * inv_denom;

    if (gamma < 0.0) return false;

    if (beta + gamma > 1.0) return false;

    double e3 = a * p - b * r + d * ss;
    double t_value = e3 * inv_denom;

	if (t_value < kEpsilon) return false;

    Vector3D normal = (this->v0 - this->v1) ^ (this->v0 - this->v2);
    normal.normalize();

    t = t_value;

    return true;
}

BBox Triangle::getBBox() const
{
    return BBox(min(min(v0, v1), v2), max(max(v0,v1), v2));
}