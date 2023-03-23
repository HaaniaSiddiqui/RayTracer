#include "GlossySpecular.hpp"
#include "../Utilities/Constants.hpp"
#include <math.h>

// constructor and operator overloading
GlossySpecular::GlossySpecular(float ks_, float exp_, RGBColor cs_) : BRDF(), ks(ks_), E(exp_), cs(cs_) {}
GlossySpecular::GlossySpecular(const GlossySpecular &lambertian) : BRDF(lambertian),
                                                                   ks(lambertian.ks),
                                                                   E(lambertian.E),
                                                                   cs(lambertian.cs)
{
}

GlossySpecular &GlossySpecular::operator=(const GlossySpecular &lambertian)
{
    BRDF::operator=(lambertian);
    ks = lambertian.ks;
    E = lambertian.E;
    cs = lambertian.cs;
    return (*this);
}

// methods
float GlossySpecular::get_ks() const
{
    return ks;
}

void GlossySpecular::set_ks(const float ks)
{
    this->ks = ks;
}

void GlossySpecular::set_exp(const float exp_)
{
    this->E = exp_;
}

float GlossySpecular::get_exp() const
{
    return E;
}

RGBColor GlossySpecular::get_cs() const
{
    return cs;
}

void GlossySpecular::set_cs(const RGBColor cs)
{
    this->cs = cs;
}

void GlossySpecular::set_samples(const int num_samples, const float exp)
{
}

RGBColor GlossySpecular::f(const ShadeInfo &sinfo, const Vector3D &wo, const Vector3D &wi) const
{
    RGBColor L;
    float ndotwi = sinfo.normal * wi;
    Vector3D r(-wi + 2.0 * sinfo.normal * ndotwi);
    float rdotwo = r * wo;
    if (rdotwo > 0.0)
    {
        L = cs * ks * std::pow(rdotwo, E);
    }
    return (L);
}

RGBColor GlossySpecular::sample_f(const ShadeInfo &sinfo, const Vector3D &wo,
                                  Vector3D &wi, float &pdf) const
{
    return RGBColor(0);
}
