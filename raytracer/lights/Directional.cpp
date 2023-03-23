#include "Directional.hpp"
#include "../geometry/Geometry.hpp"

Directional::Directional(): Light(true), ls(1.0), color(1.0), dir(0, 1, 0) {}
Directional::Directional(const Directional& dl): Light(dl), ls(dl.ls), color(dl.color), dir(dl.dir){}

Directional& Directional::operator= (const Directional& rhs) 	
{
    Light::operator= (rhs);

	this->ls = rhs.ls;
	this->color = rhs.color;
	this->dir = rhs.dir;

	return (*this);
}

Vector3D Directional::get_direction(const ShadeInfo& sr){
	return (dir);
}	

RGBColor Directional::L(const ShadeInfo& s) const {	
	return (ls * color);
}

void Directional::set_ls(const float b) { 
	this->ls = b;
}

void Directional::set_color(const float c) {
	RGBColor temp(c);
    this->color = temp;
}

void Directional::set_color(const RGBColor& c) {
	RGBColor temp(c);
    this->color = temp;
}

void Directional::set_color(const float r, const float g, const float b) {
	RGBColor temp(r, g, b);
    this->color = temp;
}

void Directional::set_direction(Vector3D d) {
	this->dir = d;
	this->dir.normalize();
}

void Directional::set_direction(float dx, float dy, float dz) {
	this->dir.x = dx; 
    this->dir.y = dy; 
    this->dir.z = dz;

	this->dir.normalize();
}

// Need to research more about shadow_hit
bool Directional::in_shadow(const Ray& ray, const ShadeInfo& sr) const {
	float t;
	int num_objects = sr.w->geometry.size();
	for(int j = 0; j < num_objects; j++){
		if(sr.w->geometry[j]->shadow_hit(ray, t)){
			return true;
		}
	}

	return false;
}