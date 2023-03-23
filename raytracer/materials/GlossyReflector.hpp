#pragma once

#include "Phong.hpp"
#include "../BRDF/GlossySpecular.hpp"

class GlossyReflector : public Phong
{
private:
    GlossySpecular *glossy_specular_brdf;

public:
    // constructors, copy constructor
    GlossyReflector();
    GlossyReflector(const GlossyReflector &ref);
    GlossyReflector &operator=(const GlossyReflector &ref);

    // setter and getter functions
    void set_samples(const int num_samples, const float exp);
    void set_kr(const float k);
    void set_exp(const float exp);

    // set area light
    virtual RGBColor area_light_shade(ShadeInfo &sinfo);
};
