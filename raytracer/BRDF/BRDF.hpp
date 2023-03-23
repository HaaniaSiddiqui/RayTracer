#pragma once

#include "../Samplers/Sampler.hpp"
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/ShadeInfo.hpp"

class BRDF
{
protected:
    Sampler *sampler_ptr;

public:
    // constructor and operator overloading
    BRDF();
    BRDF(const BRDF &brdf) = default;
    BRDF(Sampler *sampler);
    BRDF &operator=(const BRDF &rhs) = default;

    virtual ~BRDF() = default;

    // methods to sample
    void set_sampler(Sampler *sampler);

    virtual RGBColor f(const ShadeInfo &sinfo, const Vector3D &wi, const Vector3D &wo) const;
    virtual RGBColor sample_f(const ShadeInfo &sinfo, Vector3D &wi, Vector3D &wo) const;
    virtual RGBColor sample_f(const ShadeInfo &sinfo, Vector3D &wi, Vector3D &wo, float &pdf) const;
    virtual RGBColor rho(const ShadeInfo &sinfo, const Vector3D &wi) const;
};
