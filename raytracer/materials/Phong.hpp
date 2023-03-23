#pragma once

#include "Material.hpp"
#include "../BRDF/Lambertian.hpp"
#include "../BRDF/GlossySpecular.hpp"

class Phong : public Material
{
private:
    Lambertian *ambient_brdf;
    Lambertian *diffuse_brdf;
    GlossySpecular *specular_brdf;

public:
    // constructors
    Phong(Lambertian *ambient_brdf_ = NULL, Lambertian *diffuse_brdf_ = NULL, GlossySpecular *specular_brdf_ = NULL);
    Phong(const Phong &m);

    // operator overloading
    Phong &operator=(const Phong &phong);

    // destructor
    ~Phong() = default;

    // setters and getters
    void set_ka(const float k);
    void set_kd(const float k);
    void set_ks(const float k);
    void set_exp(const float exp_);
    void set_cd(const RGBColor &c);

    // color logic
    virtual RGBColor shade(const ShadeInfo &sinfo) const override;
};
