#include "Rectangle.hpp"
#include <iostream>
#include <sstream>
#include "../utilities/Constants.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../samplers/Sampler.hpp"
#include "../utilities/BBox.hpp"

Rectangle::Rectangle(Point3D p_, Vector3D a_, Vector3D b_, Vector3D n)
    : Geometry()
    , p(p_)
    , a(a_)
    , b(b_)
    , normal(n) 
    , sampler_ptr(new Regular) 
    , area(a.length() * b.length())
    , inv_area(1.0/area)
    , a_len_squared(a.length()*a.length())
    , b_len_squared(b.length()*b.length()) {
    normal.normalize();
}


Rectangle::~Rectangle(){
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
}

void Rectangle::set_p(const Point3D p_){
    p = p_;
}

Point3D Rectangle::get_p() const {
    return p;
}

void Rectangle::set_a_b(const Vector3D a_, const Vector3D b_){
    a = a_;
    b = b_;
    normal = a ^ b;
    normal.normalize();
    area = a.length() * b.length();
    inv_area = 1.0/area;
    a_len_squared = a.length()*a.length();
    b_len_squared = b.length()*b.length();
}

void Rectangle::set_sampler(Sampler* sampler){
    if(sampler_ptr){
        delete sampler_ptr;
    }
    sampler_ptr = sampler;
}

Point3D Rectangle::sample(){
    Point3D sample_point = sampler_ptr->sample_unit_square();
    return (p + sample_point.x*a + sample_point.y*b);
}

float Rectangle::pdf(const ShadeInfo& sinfo){
    return inv_area;
}

Vector3D Rectangle::get_normal(const Point3D& p) const{
    return normal;
}

std::string Rectangle::to_string() const{
    std::stringstream stream;
    stream << "Point -> (" << this->p.x << ", " << this->p.y << ", " << this->p.z << ")" << std::endl;
    stream << "Normal -> (" << this->normal.x << ", " << this->normal.y << ", " << this->normal.z << ")" << std::endl;
    return stream.str();
}


BBox Rectangle::getBBox() const{
    return BBox();
}

bool Rectangle::hit(const Ray& ray, double& tmin, ShadeInfo& sinfo) const{
    double t = (p - ray.o) * normal / (ray.d * normal); 
	
	if (t <= kEpsilon)
		return (false);
			
	Point3D p0 = ray.o + t * ray.d;
	Vector3D d = p0 - p;
	
	double ddota = d * a;
	
	if (ddota < 0.0 || ddota > a_len_squared)
		return (false);
		
	double ddotb = d * b;
	
	if (ddotb < 0.0 || ddotb > b_len_squared)
		return (false);
		
	tmin = t;
	sinfo.normal = normal;
	sinfo.hit_point = ray.o + (t * ray.d);
    sinfo.t = t;
    sinfo.ray = ray;

	return (true);
}

bool Rectangle::shadow_hit(const Ray& ray, float& tmin) const{
    double t = (p - ray.o) * normal / (ray.d * normal); 
	
	if (t <= kEpsilon)
		return (false);
			
	Point3D p0 = ray.o + t * ray.d;
	Vector3D d = p0 - p;
	
	double ddota = d * a;
	
	if (ddota < 0.0 || ddota > a_len_squared)
		return (false);
		
	double ddotb = d * b;
	
	if (ddotb < 0.0 || ddotb > b_len_squared)
		return (false);
		
	tmin 				= t;
	return (true);
}		