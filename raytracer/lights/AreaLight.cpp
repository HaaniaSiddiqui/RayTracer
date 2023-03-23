#include "AreaLight.hpp"
#include <iostream>
#include "../Utilities/ShadeInfo.hpp"
#include "../World/World.hpp"

AreaLight::AreaLight(void)
	: 	Light(),
		object_ptr(NULL),
		material_ptr(NULL)
{}	
	
AreaLight::AreaLight(const AreaLight& light)
	: Light(light) {
	if(light.object_ptr)
		object_ptr = light.object_ptr; 
	else  object_ptr = NULL;
	
	if(light.material_ptr)
		material_ptr = light.material_ptr; 
	else  material_ptr = NULL;
}
				
AreaLight& AreaLight::operator= (const AreaLight& light) {
	Light::operator=(light);
	
	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}

	if (light.object_ptr)
		object_ptr = light.object_ptr;
		
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}

	if (light.material_ptr)
		material_ptr = light.material_ptr;

	return (*this);
}

void AreaLight::set_object(Geometry* object) {
	object_ptr = object;
	if(object_ptr){
		material_ptr = object_ptr->get_material();
	}
}

Vector3D AreaLight::get_direction(const ShadeInfo& sinfo){
	Point3D sample_point = object_ptr->sample();
	light_normal = object_ptr->get_normal(sample_point); 
	wi = sample_point - sinfo.hit_point; 
	wi.normalize();
	
	return (wi);
}

RGBColor AreaLight::L(const ShadeInfo& sinfo) const {
	float ndotd = -light_normal * wi; 
	
	if (ndotd > 0.0)		
		return (material_ptr->get_Le(sinfo)); 
	else
		return (black);
}

bool AreaLight::in_shadow(const Ray& ray, const ShadeInfo& sinfo) const {
	float t;
	int num_objects = sinfo.w->geometry.size();
	float ts = (sample_point - ray.o) * ray.d;
	
	for (int j = 0; j < num_objects; j++)
		if (sinfo.w->geometry[j]->shadow_hit(ray, t) && t < ts)
			return (true); 
		
	return (false);     
}

float AreaLight::G(const ShadeInfo& sinfo) const {
	float ndotd = -light_normal * wi;
	float d2 	= sample_point.d_squared(sinfo.hit_point);
		
	return (ndotd / d2);
}

float AreaLight::pdf(const ShadeInfo& sinfo) const {
	return (object_ptr->pdf(sinfo));
}


