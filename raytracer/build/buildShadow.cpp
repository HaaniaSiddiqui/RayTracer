#include <iostream>
#include "../cameras/Perspective.hpp"
#include "../cameras/Parallel.hpp"
#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"
#include "../tracer/Basic.hpp"
#include "../lights/Light.hpp"
#include "../lights/Ambient.hpp"
#include "../lights/PointLight.hpp"
#include "../lights/Directional.hpp"
#include "../materials/Cosine.hpp"
#include "../materials/Matte.hpp"
#include "../materials/Reflective.hpp"
#include "../samplers/Simple.hpp"
#include "../samplers/Regular.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"
#include "../world/World.hpp"

void
World::build(void) {
	// view plane
    vplane.top_left.x = -200;
    vplane.top_left.y = 200;
    vplane.top_left.z = 100;
    vplane.bottom_right.x = 200;
    vplane.bottom_right.y = -200;
    vplane.bottom_right.z = 100;
    vplane.hres = 600;
    vplane.vres = 600;
    vplane.max_depth = 0;
    vplane.s = 1.0;

    // 16 regular samples
    vplane.num_samples = 16;

    bg_color = black;  // background color.

    // camera and sampler.
    set_camera(new Perspective(0, 100, 200));
    set_tracer(new Basic(this));
    sampler_ptr = new Regular(camera_ptr, &vplane);

    //Lighting

    // Uncomment the following line and comment out the two point lights to see directional shadows

    // Directional* light_ptr = new Directional();
    // light_ptr->set_ls(3.0);
    // light_ptr->set_shadows(true);
    // light_ptr->set_color(RGBColor(1.0, 1.0, 1.0));
    // light_ptr->set_direction(Vector3D(-200, 50, 50));
    // add_light(light_ptr);


    PointLight* light_ptr = new PointLight;
    light_ptr->set_ls(3.0);
    light_ptr->set_shadows(true);
    light_ptr->set_color(RGBColor(1.0, 1.0, 1.0));
    light_ptr->set_location(Point3D(-200, 50, 50));
    add_light(light_ptr);

    PointLight* light_ptr2 = new PointLight;
    light_ptr2->set_ls(3.0);
    light_ptr2->set_shadows(true);
    light_ptr2->set_color(RGBColor(1.0, 1.0, 1.0));
    light_ptr2->set_location(Point3D(200, 50, 50));
    add_light(light_ptr2);


    //Materials and Spheres
	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.65);
	matte_ptr1->set_cd(RGBColor(0, 1, 1));

	Sphere*	sphere_ptr1 = new Sphere(Point3D(75, -10, 0), 50);
	sphere_ptr1->set_material(matte_ptr1);
	add_geometry(sphere_ptr1);


	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.15);
	matte_ptr2->set_kd(0.5);
	matte_ptr2->set_cd(RGBColor(0.4, 0.2, 0.0));

	Plane* plane_ptr = new Plane(Point3D(0, -50, 0), Vector3D(0, 1, 0));
	plane_ptr->set_material(matte_ptr2);
	add_geometry(plane_ptr);


    // Comment out the following sphere and its material to see shadows for just one sphere
    Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.25);
	matte_ptr3->set_kd(0.65);
	matte_ptr3->set_cd(RGBColor(0, 1, 0));

    Sphere*	sphere_ptr2 = new Sphere(Point3D(-75, -10, 0), 50);
	sphere_ptr2->set_material(matte_ptr3);
	add_geometry(sphere_ptr2);
}



