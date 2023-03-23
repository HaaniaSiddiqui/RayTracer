#pragma once

#include "Light.hpp"
#include "../utilities/Point3D.hpp"

class PointLight : public Light
{
private:
    Point3D location;

public:
    // constructors

    PointLight(Point3D location = Point3D(0), float ls_ = 1.0, RGBColor color_ = 1.0, bool shadows_ = false);
    PointLight(PointLight &point);

    // destructor
    virtual ~PointLight() = default;

    // setter getters

    Point3D get_location() const;
    void set_location(const Point3D location_);
    void set_location(const float x, const float y, const float z);
    void set_ls(const float c);
    void set_color(const RGBColor c);

    // get direction
    Vector3D get_direction(const ShadeInfo &sinfo);
    RGBColor L(const ShadeInfo &sinfo) const;

    // check if in shadow

    virtual bool in_shadow(const Ray &ray, const ShadeInfo &sr) const;
    void set_shadows(bool s);
};
