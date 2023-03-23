#pragma once

#include "Material.hpp"
#include "../utilities/RGBColor.hpp"

class Emissive : public Material
{
private:
    float ls;
    RGBColor ce;

public:
    // Copy constuctor and assignment operator.
    Emissive(const float ls_ = 1, const RGBColor ce_ = RGBColor(1));
    Emissive(const Emissive &emissive);
    Emissive &operator=(const Emissive &emissive);

    // setter, getters
    void set_ce(const float r, const float g, const float b);
    void set_ce(const float a);
    void set_ce(const RGBColor ce_);
    virtual RGBColor get_Le(const ShadeInfo &sinfo) const;

    // shading and lighting functions
    void scale_radiance(const float ls_);
    virtual RGBColor shade(const ShadeInfo &sinfo) const;
    virtual RGBColor area_light_shade(ShadeInfo &sinfo);
};
