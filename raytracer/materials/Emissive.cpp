#include "Emissive.hpp"
#include "../utilities/ShadeInfo.hpp"

// Copy constuctor and assignment operator.
Emissive::Emissive(const float ls_, const RGBColor ce_) : Material(), ls(ls_), ce(ce_) {}
Emissive::Emissive(const Emissive &emissive) : Material(emissive), ls(emissive.ls), ce(emissive.ce) {}

Emissive &Emissive::operator=(const Emissive &emissive)
{
    Material::operator=(emissive);
    ls = emissive.ls;
    ce = emissive.ce;
    return (*this);
}

// radiance
void Emissive::scale_radiance(const float ls_)
{
    this->ls = ls_;
}

// setters and getters

void Emissive::set_ce(const float r, const float g, const float b)
{
    this->ce = RGBColor(r, g, b);
}

void Emissive::set_ce(const float a)
{
    this->ce = RGBColor(a);
}

void Emissive::set_ce(const RGBColor ce_)
{
    this->ce = ce_;
}

RGBColor Emissive::get_Le(const ShadeInfo &sinfo) const
{
    return ls * ce;
}

// set shade
RGBColor Emissive::shade(const ShadeInfo &sinfo) const
{
    return RGBColor(0);
}

RGBColor Emissive::area_light_shade(ShadeInfo &sinfo)
{
    if (-sinfo.normal * sinfo.ray.d > 0.0)
    {
        return (ls * ce);
    }
    else
    {
        return RGBColor(0);
    }
}
