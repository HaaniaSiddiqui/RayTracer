#include <iostream>
#include "Plane.hpp"
#include <sstream>
#include "../utilities/Ray.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Constants.hpp"

Plane::Plane(): a(0), n(0, 1, 0) {}
Plane::Plane(const Plane& object): a(object.a), n(object.n) {}

Plane::Plane(const Point3D &pt,const Vector3D &n)
{
    this->a = pt;
    this->n = n;
    this->n.normalize();
}

Plane& Plane::operator=(const Plane& rhs)
{
    this->a = rhs.a;
    this->n = rhs.n;
    return *this;
}

std::string Plane::to_string() const
{
    std::stringstream stream;
    stream << "Point -> (" << this->a.x << ", " << this->a.y << ", " << this->a.z << ")" << std::endl;
    stream << "Normal -> (" << this->n.x << ", " << this->n.y << ", " << this->n.z << ")" << std::endl;
    return stream.str();
}

bool Plane::hit(const Ray& ray, double& t, ShadeInfo& s) const
{
    // Reference: Ray Tracer from the Ground Up

    float t_value = ((this->a - ray.o) * this->n) / (ray.d * this->n);

    if(t_value > kEpsilon){
        t = t_value;
        s.normal = this->n;
        s.hit_point = ray.o + t * ray.d;
        s.ray = ray;
        s.t = t;

        return true;
    }

    return false;
}

bool Plane::shadow_hit(const Ray& ray, float& t) const {
	float t_value = (a - ray.o) * n / (ray.d * n);
	if(t_value > kEpsilon){
		t = t_value;
		return true;
	}
	else return false;
}

BBox Plane::getBBox() const
{
    BBox box;
    return box;
}