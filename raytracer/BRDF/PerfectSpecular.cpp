#include "PerfectSpecular.hpp"
// constructor and operator overloading

PerfectSpecular::PerfectSpecular(float kr_, RGBColor cr_) : BRDF(), kr(kr_), cr(cr_) {}
PerfectSpecular::PerfectSpecular(const PerfectSpecular &spec) : BRDF(spec), kr(spec.kr), cr(spec.cr) {}

PerfectSpecular &PerfectSpecular::operator=(const PerfectSpecular &spec)
{
    BRDF::operator=(spec);
    kr = spec.kr;
    cr = spec.cr;
    return (*this);
}

// getter and setters

float PerfectSpecular::get_kr() const
{
    return this->kr;
}

void PerfectSpecular::set_kr(const float kr)
{
    this->kr = kr;
}

RGBColor PerfectSpecular::get_cr() const
{
    return this->cr;
}

void PerfectSpecular::set_cr(const RGBColor cr)
{
    this->cr = cr;
}

// methods

RGBColor PerfectSpecular::sample_f(const ShadeInfo &sinfo, const Vector3D &wo, Vector3D &wi) const
{
    float ndotwo = sinfo.normal * wo;
    wi = (-wo + 2.0 * sinfo.normal * ndotwo);
    return (kr * cr / (sinfo.normal * wi));
}
