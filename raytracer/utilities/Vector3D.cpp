#include <iostream>
#include <cmath>
#include <sstream>
#include "Vector3D.hpp"
#include "Point3D.hpp"


Vector3D::Vector3D(): x(0), y(0), z(0) {}
Vector3D::Vector3D(double c): x(c), y(c), z(c) {}
Vector3D::Vector3D(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}
Vector3D::Vector3D(const Point3D& p): x(p.x), y(p.y), z(p.z) {}

Vector3D& Vector3D::operator=(const Point3D& rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    this->z = rhs.z;

    return *this;
}

std::string Vector3D::to_string() const
{
    std::stringstream stream;
    stream << "Vector -> (" << x << "," << y << "," << z << ")" << std::endl;
    return stream.str();
}

Vector3D Vector3D::operator-() const
{
    return Vector3D(-x, -y, -z);
}

Vector3D Vector3D::operator+(const Vector3D& v) const
{
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D& Vector3D::operator+=(const Vector3D& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D& v) const
{
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D& Vector3D::operator-=(const Vector3D& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3D Vector3D::operator*(const double a) const
{
    return Vector3D(x *a , y * a, z * a);
}

Vector3D Vector3D::operator/(const double a) const
{
    return Vector3D(x / a, y / a, z / a);
}

void Vector3D::normalize()
{
    double len = Vector3D::length();
    this->x /= len;
    this->y /= len;
    this->z /= len;
}

double Vector3D::length() const
{
    return std::sqrt(this->len_squared());
}

double Vector3D::len_squared() const
{
    double a, b, c;
    a = std::pow(x, 2);
    b = std::pow(y, 2);
    c = std::pow(z, 2);
    return (a + b + c);
}

double Vector3D::operator*(const Vector3D& b) const
{
    return (x * b.x + y * b.y + z * b.z);
}

Vector3D Vector3D::operator^(const Vector3D& v) const
{
    return Vector3D((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
}

Vector3D operator*(const double a, const Vector3D& v)
{
    return Vector3D(a * v.x, a * v.y, a * v.z);
}

// int main(){

//     Vector3D v;
//     Point3D p(1, 1, 1);
//     v = p;
//     Vector3D v2(1, 1, 1);
//     v = 2 * v;

//     std::cout << v.to_string();

//     return 0;
// }