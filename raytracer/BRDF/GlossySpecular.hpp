#pragma once

#include "BRDF.hpp"

class GlossySpecular : public BRDF
{
protected:
    float ks;
    float E;
    RGBColor cs;

public:
    // constructor and operator overloading
    GlossySpecular(float ks_ = 0.0, float exp_ = 0.0, RGBColor cs_ = RGBColor(0));
    GlossySpecular(const GlossySpecular &lambertian);
    GlossySpecular &operator=(const GlossySpecular &lambertian);

    // working methods
    float get_ks() const;
    void set_ks(const float ks);
    float get_exp() const;
    void set_exp(const float exp_);
    RGBColor get_cs() const;
    void set_cs(const RGBColor cs);

    void set_samples(const int num_samples, const float exp);

    virtual RGBColor sample_f(const ShadeInfo &sinfo, const Vector3D &wo,
                              Vector3D &wi, float &pdf) const;
    virtual RGBColor f(const ShadeInfo &sinfo, const Vector3D &wo, const Vector3D &wi) const;
};
