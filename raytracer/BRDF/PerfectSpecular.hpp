#pragma once

#include "BRDF.hpp"

class PerfectSpecular : public BRDF
{
protected:
    float kr;
    RGBColor cr;

public:
    // constructor and operator overloading
    PerfectSpecular(float kr_ = 0.0, RGBColor cr_ = RGBColor(1.0));
    PerfectSpecular(const PerfectSpecular &spec);
    PerfectSpecular &operator=(const PerfectSpecular &spec);

    // getter and setters
    float get_kr() const;
    void set_kr(const float kr);

    RGBColor get_cr() const;
    void set_cr(const RGBColor cr);

    // methods
    virtual RGBColor sample_f(const ShadeInfo &sinfo, const Vector3D &wo, Vector3D &wi) const;
};
