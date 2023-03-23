#include <iostream>
#include "Cosine.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/ShadeInfo.hpp"

// Constructors.
Cosine::Cosine() : color(0) {}
Cosine::Cosine(float c) : color(c) {}
Cosine::Cosine(float r, float g, float b) : color(r, g, b) {}
Cosine::Cosine(const RGBColor &c) : color(c) {}

// Copy constuctor and assignment operator.
Cosine::Cosine(const Cosine &other)
{
    this->color = other.color;
}

Cosine &Cosine::operator=(const Cosine &other)
{
    this->color = other.color;
    return *this;
}

/* Returned shade is: color * cos \theta.
     \theta is the angle between the normal at the hit point and the ray.
     Assuming unit vectors, cos \theta = dot product of normal and -ray.dir.
  */
RGBColor Cosine::shade(const ShadeInfo &sinfo) const
{
    return color * (sinfo.normal * -sinfo.ray.d);
}
