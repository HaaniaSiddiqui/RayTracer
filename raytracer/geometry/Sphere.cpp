#include <iostream>
#include <sstream>
#include <cmath>
#include "Sphere.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Constants.hpp"

Sphere::Sphere(): c(0), r(0) {}
Sphere::Sphere(const Point3D& center, double radius): c(center), r(radius) {}
Sphere::Sphere(const Sphere& object): c(object.c), r(object.r) {}

Sphere& Sphere::operator=(const Sphere& rhs)
{
    this->c = rhs.c;
    this->r = rhs.r;
    return *this;
}

std::string Sphere::to_string() const
{
    std::stringstream stream;
    stream << "Center -> (" << this->c.x << ", " << this->c.y << ", " << this->c.z << ")" << std::endl;
    stream << "Radius -> " << r << std::endl;
    return stream.str();
}

bool Sphere::hit(const Ray& ray, double& t, ShadeInfo& s) const
{
    double t_val;
    Vector3D temp = ray.o - this->c;
    double a = ray.d * ray.d;
    double b = 2 * temp * ray.d;
    double c = (temp * temp) - (this->r * this->r);
    double disc = (b * b) - (4 * a * c);

    if(disc < 0){
        return false;
    }
    else{
        double e = std::sqrt(disc);

        double denom = 2 * a;
        t_val = (-b - e) / denom;

        if(t_val > kEpsilon){
            t = t_val;
            s.normal = (temp + t * ray.d) / this->r;
            s.hit_point = ray.o + t * ray.d;
            s.t = t;
            s.ray = ray;
            return true;
        }

        t_val = (-b + e) / denom;

        if(t_val > kEpsilon){
            t = t_val;
            s.normal = (temp + t * ray.d) / this->r;
            s.hit_point = ray.o + t * ray.d;
            s.t = t;
            s.ray = ray;
            return true;
        }
    }

    return false;
}

bool Sphere::shadow_hit(const Ray& ray, float& t) const
{
    double t_val;
    Vector3D temp = ray.o - this->c;
    double a = ray.d * ray.d;
    double b = 2 * temp * ray.d;
    double c = (temp * temp) - (this->r * this->r);
    double disc = (b * b) - (4 * a * c);

    if(disc < 0){
        return false;
    }
    else{
        double e = std::sqrt(disc);

        double denom = 2 * a;
        t_val = (-b - e) / denom;

        if(t_val > kEpsilon){
            t = t_val;
            return true;
        }

        t_val = (-b + e) / denom;

        if(t_val > kEpsilon){
            t = t_val;
            return true;
        }
    }

    return false;
}


BBox Sphere::getBBox() const
{
    // Resource: https://gamedev.stackexchange.com/questions/159710/getting-the-bounding-box-of-a-sphere

    Point3D min(this->c.x - r, this->c.y - r, this->c.z - r);
    Point3D max(this->c.x + r, this->c.y + r, this->c.z + r);
    BBox box(min, max);
    return box;
}