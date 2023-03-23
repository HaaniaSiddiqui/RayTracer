#include "Light.hpp"
//Credits - Kevin Suffern

Light::Light(const bool shadows_) : shadows(shadows_), ls(1.0), color(RGBColor(1.0))
{
}

Light::Light(const Light &light) : shadows(light.casts_shadows()), ls(1.0), color(RGBColor(1.0))
{
}

Light &Light::operator=(const Light &rhs)
{
    if (this == &rhs)
        return (*this);

    return (*this);
}

bool Light::casts_shadows() const
{
    return shadows;
}

void Light::set_shadows(const bool shadows_)
{
    shadows = shadows_;
}

void Light::set_color(const RGBColor &c)
{
    color = c;
}

float Light::G(const ShadeInfo &sinfo) const
{
    return (1.0);
}

float Light::pdf(const ShadeInfo &sinfo) const
{
    return (1.0);
}
