#include "PointLight.hpp"
#include "../Utilities/ShadeInfo.hpp"
#include "../World/World.hpp"
#include "../geometry/Geometry.hpp"

// constructors
PointLight::PointLight(Point3D location_, float ls_, RGBColor color_, bool shadows_) : Light(),
                                                                                       location(location_)
{
    this->ls = ls_;
    this->shadows = shadows_;
    this->color = color_;
}

PointLight::PointLight(PointLight &point) : Light(point), location(point.get_location()) {}

// setter getters

Point3D PointLight::get_location() const
{
    return location;
}

void PointLight::set_location(const Point3D location_)
{
    location = location_;
}

void PointLight::set_color(const RGBColor c)
{
    this->color = c;
}

void PointLight::set_location(const float x, const float y, const float z)
{
    location = Point3D(x, y, z);
}

// get direction

Vector3D PointLight::get_direction(const ShadeInfo &sr)
{
    Vector3D dir = (location - sr.hit_point);
    dir.normalize();
    return dir;
}

RGBColor PointLight::L(const ShadeInfo &sinfo) const
{
    return (ls * color);
}

void PointLight::set_ls(const float c)
{
    this->ls = c;
}

void PointLight::set_shadows(bool s)
{
    shadows = s;
}

// Need to research more about shadow_hit
bool PointLight::in_shadow(const Ray &ray, const ShadeInfo &sinfo) const
{
    float t;
    int num_objects = sinfo.w->geometry.size();
    float d = location.distance(ray.o);

    for (int j = 0; j < num_objects; j++)
    {
        if (sinfo.w->geometry[j]->shadow_hit(ray, t) && t < d)
        {
            return true;
        }
    }
    return false;
}
