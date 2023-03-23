#include "Lambertian.hpp"

Lambertian::Lambertian(float kd_, RGBColor cd_) : BRDF(), kd(kd_), cd(cd_) {}
Lambertian::Lambertian(const Lambertian &lambertian) : BRDF(lambertian), kd(lambertian.kd), cd(lambertian.cd) {}

// constructor and operator overloading

Lambertian &Lambertian::operator=(const Lambertian &lambertian)
{
    BRDF::operator=(lambertian);
    kd = lambertian.kd;
    cd = lambertian.cd;
    return (*this);
}

// getter and setters

float Lambertian::get_kd() const
{
    return this->kd;
}

void Lambertian::set_kd(const float kd)
{
    this->kd = kd;
}

RGBColor Lambertian::get_cd() const
{
    return this->cd;
}

void Lambertian::set_cd(const RGBColor cd)
{
    this->cd = cd;
}

// methods
RGBColor Lambertian::f(const ShadeInfo &sinfo, const Vector3D &wi, const Vector3D &wo) const
{
    return (this->kd * this->cd * invPI);
}

RGBColor Lambertian::rho(const ShadeInfo &sinfo, const Vector3D &wi) const
{
    return (this->kd * this->cd);
}
