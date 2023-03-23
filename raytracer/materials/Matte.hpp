#pragma once

#include "Material.hpp"
#include "../BRDF/Lambertian.hpp"

class Matte : public Material
{
private:
    Lambertian *ambient_brdf;
    Lambertian *diffuse_brdf;

public:
    // default and copy constuctor
    Matte(Lambertian *ambient_brdf_ = NULL, Lambertian *diffuse_brdf_ = NULL);
    Matte(const Matte &m);

    // assignment operator
    Matte &operator=(const Matte &matte);

    // destructor
    ~Matte() = default;

    // getter and setters
    void set_ka(const float k);
    void set_kd(const float k);
    void set_cd(const RGBColor &c);

    // color logic
    virtual RGBColor shade(const ShadeInfo &sinfo) const override;
    virtual RGBColor area_light_shade(ShadeInfo &sinfo);
};
