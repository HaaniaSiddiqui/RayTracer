#include "Ambient.hpp"

// constructor
Ambient::Ambient() : Light(), ls(1.0), color(1.0) {}
Ambient::Ambient(const Ambient &a) : Light(a), ls(a.ls), color(a.color) {}

//operator overloading

Ambient &Ambient::operator=(const Ambient &rhs)
{
	if (this == &rhs)
		return (*this);

	Light::operator=(rhs);

	ls = rhs.ls;
	color = rhs.color;

	return (*this);
}

Vector3D Ambient::get_direction(const ShadeInfo &s)
{
	return (Vector3D(0.0));
}

RGBColor Ambient::L(const ShadeInfo &sr) const
{
	return (ls * color);
}

// setter getters

void Ambient::set_color(const float c)
{
	RGBColor temp(c);
	this->color = temp;
}

void Ambient::set_color(const RGBColor &c)
{
	RGBColor temp(c);
	this->color = temp;
}

void Ambient::set_color(const float r, const float g, const float b)
{
	RGBColor temp(r, g, b);
	this->color = temp;
}

void Ambient::set_ls(const float b)
{
	this->ls = b;
}

// check if in shadow
bool Ambient::in_shadow(const Ray &ray, const ShadeInfo &sr) const
{
	return false;
}
