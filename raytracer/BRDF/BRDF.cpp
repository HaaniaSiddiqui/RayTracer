#include "BRDF.hpp"

// constructor and operator overloading
BRDF::BRDF() : sampler_ptr(NULL) {}
BRDF::BRDF(Sampler *sampler) : sampler_ptr(sampler) {}

// set sampler
void BRDF::set_sampler(Sampler *sampler)
{
    this->sampler_ptr = sampler;
}

// methods
RGBColor BRDF::f(const ShadeInfo &sinfo, const Vector3D &wo, const Vector3D &wi) const
{
    return black;
}

RGBColor BRDF::sample_f(const ShadeInfo &sinfo, Vector3D &wo, Vector3D &wi) const
{
    return black;
}

RGBColor BRDF::sample_f(const ShadeInfo &sinfo, Vector3D &wo, Vector3D &wi, float &pdf) const
{
    return black;
}

RGBColor BRDF::rho(const ShadeInfo &sinfo, const Vector3D &wo) const
{
    return black;
}
