#pragma once

#include "BRDF.hpp"

class Lambertian : public BRDF
{
protected:
    float kd;
    RGBColor cd;

public:
    // constructor and operator overloading
    Lambertian(float kd_ = 0.0, RGBColor cd_ = RGBColor(0.0));
    Lambertian(const Lambertian &lambertian);
    Lambertian &operator=(const Lambertian &lambertian);

    // getter and setters
    float get_kd() const;
    void set_kd(const float kd);

    RGBColor get_cd() const;
    void set_cd(const RGBColor cd);

    // methods
    virtual RGBColor f(const ShadeInfo &sinfo, const Vector3D &wi, const Vector3D &wo) const;
    virtual RGBColor rho(const ShadeInfo &sinfo, const Vector3D &wi) const;
};
