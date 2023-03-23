#pragma once

#include "Phong.hpp"
#include "../BRDF/PerfectSpecular.hpp"

class Reflective : public Phong
{
private:
    PerfectSpecular *reflective_brdf;

public:
    // Constructors.
    Reflective();

    // Copy constuctor and assignment operator.
    Reflective(const Reflective &ref);
    Reflective &operator=(const Reflective &ref);

    // getter and setters
    void set_kr(const float k);
    void set_cr(const RGBColor c);

    // get color
    virtual RGBColor shade(const ShadeInfo &sinfo) const;
};
