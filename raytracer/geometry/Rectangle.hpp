#pragma once

#include "Geometry.hpp"
#include "../Samplers/Regular.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Point3D.hpp"

class Rectangle : public Geometry
{
private:
    Point3D p;
    Vector3D a;
    Vector3D b;
    Vector3D normal;
    Sampler *sampler_ptr;
    float area;
    float inv_area;
    float a_len_squared;
    float b_len_squared;

public:
    // constructor and destructor
    Rectangle(Point3D p_ = Point3D(0), Vector3D a_ = Vector3D(0), Vector3D b_ = Vector3D(0), Vector3D n = Vector3D(0));

    ~Rectangle();

    // get string representation
    virtual std::string to_string() const;

    // get BBox
    virtual BBox getBBox() const;

    // Ray intersection. Set t and sinfo as per intersection with this object.
    virtual bool hit(const Ray &ray, double &t, ShadeInfo &sinfo) const;
    virtual bool shadow_hit(const Ray &ray, float &tmin) const;

    // setter and getters
    void set_p(const Point3D p_);
    Point3D get_p() const;
    void set_a_b(const Vector3D a_, const Vector3D b_);
    virtual Vector3D get_normal(const Point3D &p) const;
    void set_sampler(Sampler *sampler);

    // methods
    virtual Point3D sample();
    virtual float pdf(const ShadeInfo &sinfo);
};
