#include "Reflective.hpp"
#include <iostream>
#include "../world/World.hpp"
#include "../tracer/Tracer.hpp"

// Copy constuctor and normal constructors
Reflective::Reflective() : Phong(), reflective_brdf(new PerfectSpecular) {}
Reflective::Reflective(const Reflective &ref) : Phong(ref)
{
    if (ref.reflective_brdf)
    {
        reflective_brdf = ref.reflective_brdf;
    }
    else
    {
        reflective_brdf = new PerfectSpecular;
    }
}

// assignment operato
Reflective &Reflective::operator=(const Reflective &ref)
{
    Phong::operator=(ref);
    if (ref.reflective_brdf)
    {
        reflective_brdf = ref.reflective_brdf;
    }
    else
    {
        reflective_brdf = new PerfectSpecular;
    }

    return (*this);
}

// getter and setters

void Reflective::set_kr(const float k)
{
    if (reflective_brdf)
    {
        reflective_brdf->set_kr(k);
    }
}

void Reflective::set_cr(const RGBColor c)
{
    reflective_brdf->set_cr(c);
}

// get color
RGBColor Reflective::shade(const ShadeInfo &sinfo) const
{
    RGBColor L(Phong::shade(sinfo));
    Vector3D wo = -sinfo.ray.d;
    Vector3D wi;
    RGBColor fr = reflective_brdf->sample_f(sinfo, wo, wi);
    Ray reflective_ray(sinfo.hit_point, wi);
    reflective_ray.w = sinfo.depth + 1;

    L += fr * sinfo.w->tracer_ptr->trace_ray(reflective_ray, sinfo.depth + 1) * (sinfo.normal * wi);

    return L;
}
