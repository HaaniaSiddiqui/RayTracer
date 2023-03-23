
#include <iostream>
#include "../cameras/Perspective.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Plane.hpp"
#include "../materials/Matte.hpp"
#include "../geometry/Rectangle.hpp"
#include "../tracer/Basic.hpp"
#include "../tracer/AreaLighting.hpp"
#include "../lights/AreaLight.hpp"
#include "../materials/Cosine.hpp"
#include "../materials/Emissive.hpp"
#include "../samplers/Simple.hpp"
#include "../utilities/Constants.hpp"
#include "../world/World.hpp"


void
World::build(void) {
  // View plane  .
  vplane.top_left.x = -20;
  vplane.top_left.y = 20;
  vplane.top_left.z = 20;
  vplane.bottom_right.x = 20;
  vplane.bottom_right.y = -20;
  vplane.bottom_right.z = 20;
  vplane.hres = 1000;
  vplane.vres = 1000;
  vplane.max_depth = 0;
  vplane.num_samples = 1;
  vplane.s = 1.0;

  bg_color = black;

  // Camera and sampler.
  set_camera(new Perspective(0, 0, 40));
  set_tracer(new AreaLighting(this));
  sampler_ptr = new Regular(camera_ptr, &vplane);
  
  Emissive* emissive_ptr = new Emissive;
  emissive_ptr->scale_radiance(1.0);
  emissive_ptr->set_ce(white);

  Rectangle* rect = new Rectangle(Point3D(0, 0, -10), Vector3D(0, 10, 0), Vector3D(0, 0, 10), Vector3D(1, 0, 1));
  rect->set_material(emissive_ptr);
  rect->set_sampler(sampler_ptr);
  add_geometry(rect);

  AreaLight* area_light_ptr = new AreaLight;
  area_light_ptr->set_object(rect);
  area_light_ptr->set_shadows(true);
  add_light(area_light_ptr);

  Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.25); 
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(RGBColor(1.0, 1.0, 0.0)); 

  Sphere* sphere_ptr = new Sphere(Point3D(8, 0, 0), 3);
  sphere_ptr->set_material(matte_ptr1);
  add_geometry(sphere_ptr);


  Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.25); 
	matte_ptr2->set_kd(0.75);
	matte_ptr2->set_cd(RGBColor(0.0, 1.0, 0.0)); 

  Sphere* sphere_ptr2 = new Sphere(Point3D(26, 0, 0), 3);
  sphere_ptr2->set_material(matte_ptr2);
  add_geometry(sphere_ptr2);


  Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_ka(0.1); 
	matte_ptr3->set_kd(0.90);
	matte_ptr3->set_cd(blue);
  

	Plane* plane_ptr = new Plane(Point3D(0.0), Vector3D(0, 1, 0)); 
	plane_ptr->set_material(matte_ptr3);
	add_geometry(plane_ptr);
}
