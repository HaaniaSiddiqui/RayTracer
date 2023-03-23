#include <iostream>
#include <cmath>
#include <sstream>
#include "RGBColor.hpp"

RGBColor::RGBColor() : r(0), g(0), b(0) {}
RGBColor::RGBColor(float c) : r(c), g(c), b(c) {}
RGBColor::RGBColor(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}

std::string RGBColor::to_string() const
{
    std::stringstream stream;
    stream << "Color -> (" << r << "," << g << "," << b << ")" << std::endl;
    return stream.str();
}

RGBColor RGBColor::operator+(const RGBColor &c) const
{
    return RGBColor(r + c.r, g + c.g, b + c.b);
}

RGBColor &RGBColor::operator+=(const RGBColor &c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    return *this;
}

RGBColor RGBColor::operator*(const float a) const
{
    return RGBColor(r * a, g * a, b * a);
}

RGBColor &RGBColor::operator*=(const float a)
{
    r *= a;
    g *= a;
    b *= a;
    return *this;
}

RGBColor RGBColor::operator/(const float a) const
{
    return RGBColor(r / a, g / a, b / a);
}

RGBColor &RGBColor::operator/=(const float a)
{
    r /= a;
    g /= a;
    b /= a;
    return *this;
}

RGBColor RGBColor::operator*(const RGBColor &c) const
{
    return RGBColor(r * c.r, g * c.g, b * c.b);
}

bool RGBColor::operator==(const RGBColor &c) const
{
    return (r == c.r && g == c.g && b == c.b);
}

RGBColor RGBColor::powc(float p) const
{
    float c1, c2, c3;
    c1 = std::pow(r, p);
    c2 = std::pow(g, p);
    c3 = std::pow(b, p);

    return RGBColor(c1, c2, c3);
}

float RGBColor::average() const
{
    float avg = (r + g + b) / 3;
    return avg;
}

RGBColor operator*(const float a, const RGBColor &c)
{
    return RGBColor(a * c.r, a * c.g, a * c.b);
}
