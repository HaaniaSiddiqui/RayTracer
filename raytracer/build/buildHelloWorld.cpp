
/**
   This builds a simple scene that consists of a sphere, a triangle, and a
   plane.
   Parallel viewing is used with a single sample per pixel.
*/

#include "../cameras/Perspective.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"

#include "../materials/Cosine.hpp"
#include "../materials/Matte.hpp"

#include "../samplers/Simple.hpp"
#include "../samplers/Regular.hpp"

#include "../utilities/Constants.hpp"
#include "../tracer/AreaLighting.hpp"
#include "../lights/Ambient.hpp"

#include "../lights/PointLight.hpp"

#include "../world/World.hpp"
#include "../tracer/Basic.hpp"

void
World::build(void) {
  // View plane  .
  vplane.top_left.x = -10;
  vplane.top_left.y = 10;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = 10;
  vplane.bottom_right.y = -10;
  vplane.bottom_right.z = 10;
  vplane.hres = 400;
  vplane.vres = 400;
  vplane.num_samples = 1;
  vplane.max_depth = 0;
  vplane.s = 1.0;

  // Background color.  
  bg_color = black;
  
  // Camera and sampler.
  set_camera(new Perspective(0, 0, 20));
  sampler_ptr = new Simple(camera_ptr, &vplane);
  tracer_ptr = new Basic(this);


  PointLight* light_ptr = new PointLight;
  light_ptr->set_location(50, 50, 50);
  light_ptr->set_ls(3.0);
  light_ptr->set_color(RGBColor(1,1,1));
  light_ptr->set_shadows(true);
  add_light(light_ptr);

  Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.65);
	matte_ptr1->set_cd(RGBColor(1, 0, 0));

  Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.25);
	matte_ptr2->set_kd(0.65);
	matte_ptr2->set_cd(RGBColor(0, 0, 1));

  Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.25);
	matte_ptr3->set_kd(0.65);
	matte_ptr3->set_cd(RGBColor(0, 1, 0));
	
  // sphere
  Sphere* sphere_ptr = new Sphere(Point3D(-3, 2, 0), 5); 
  sphere_ptr->set_material(matte_ptr1);
  add_geometry(sphere_ptr);
  
  // triangle
  Point3D a(2.5, -5, 1); 
  Point3D b(14, -1, 0); 
  Point3D c(8.5, 5, 0.5); 
  Triangle* triangle_ptr = new Triangle(a, b, c);
  triangle_ptr->set_material(matte_ptr2);
  add_geometry(triangle_ptr);

  // plane
  Plane* plane_ptr = new Plane(Point3D(0,1,0), Vector3D(0, 10, 2)); 
  plane_ptr->set_material(matte_ptr3);  // green
  add_geometry(plane_ptr);
}
