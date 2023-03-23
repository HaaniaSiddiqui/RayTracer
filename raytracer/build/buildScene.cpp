#include "../cameras/Perspective.hpp"

#include "../tracer/Basic.hpp"
#include "../tracer/Whitted.hpp"

#include "../geometry/Sphere.hpp"
#include "../geometry/Plane.hpp"
#include "../geometry/Grid.hpp"
#include "../samplers/Simple.hpp"
#include "../materials/Matte.hpp"
#include "../materials/Reflective.hpp"
#include "../materials/Cosine.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"
#include "../lights/Ambient.hpp"
#include "../lights/PointLight.hpp"


#include "../lights/Directional.hpp"

#include "../world/World.hpp"

void World::build(void) {
    // view plane
    vplane.top_left = Point3D(-50, 50, 50);
    vplane.bottom_right = Point3D(50, -50, 50);
    vplane.hres = 1980;
    vplane.vres = 1980;
	vplane.max_depth = 8;
	vplane.num_samples = 1;
	vplane.s = 1.0;
	//Grid pointer
    Grid* grid_ptr=new Grid;
	//Colors
    RGBColor brown(0.71, 0.40, 0.16);  // brown
    RGBColor lightGreen(0.65, 1, 0.30);
    RGBColor lightPurple(0.65, 0.3, 1);
	RGBColor black(0, 0, 0);
	RGBColor red(1, 0, 0);
	RGBColor beige(1, 0.89, 0.77);
	RGBColor teal(0, 0.5,0.5);
	RGBColor skin(0.96, 0.64, 0.38);
	RGBColor py(1, 1, 0.78);
	RGBColor yellow(0.7, 0.7, 0.08);
	RGBColor blue(0,0,1);



    // Background color.
    bg_color = black;

    // camera and sampler.
    set_camera(new Perspective(0, 0, 100)); 
    //tracer for reflection
	set_tracer(new Whitted(this));
    sampler_ptr = new Simple(camera_ptr, &vplane);

	//Lighting
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->set_ls(1.0);
	set_ambient(ambient_ptr);

    Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(0.45);
	matte_ptr->set_kd(0.75);
	matte_ptr->set_cd(white);   //white matte

	Matte* matte_ptr_r = new Matte;
	matte_ptr_r->set_ka(0.45);
	matte_ptr_r->set_kd(0.75);
	matte_ptr_r->set_cd(red);   // red matte
    
	//white point light to illuminate the scene
	PointLight* light_ptrrr = new PointLight;
	light_ptrrr->set_location(50, 50, 10);
	light_ptrrr->set_ls(50.0);
	add_light(light_ptrrr);
	PointLight* light_ptrrrr = new PointLight;
	light_ptrrrr->set_location(0, 0, 50);
	light_ptrrrr->set_ls(50.0);
	add_light(light_ptrrrr);
    
	//constants for reflection
	float ka = 0.75;
	float kd = 0.75;
	float ks = 0.1;
	float e = 20.0;
	float kr = 1.0;
    //reflective pointer
    Reflective* reflective_ptr2 = new Reflective;
	reflective_ptr2->set_ka(ka);
	reflective_ptr2->set_kd(kd);
	reflective_ptr2->set_ks(ks);
	reflective_ptr2->set_cd(lightPurple);    	// yellow
	reflective_ptr2->set_exp(e);
	reflective_ptr2->set_kr(kr);
	//adding candle
	add_mesh("./models/csmall.ply", matte_ptr, Point3D(-50, -65, -10), Point3D(-30, -35, 10), grid_ptr);
	//
    Matte* matte_ptr_s = new Matte;
	matte_ptr->set_ka(0.45);
	matte_ptr->set_kd(0.75);
	matte_ptr->set_cd(beige);   // hand
	//sphere (globe)
	Sphere* sphere_ptr1 = new Sphere(Point3D(0, -25, -5), 30); 
	sphere_ptr1->set_material(reflective_ptr2);
	grid_ptr->add_object(sphere_ptr1);
    //Mesh models
	add_mesh("./models/curtains1.ply", matte_ptr_r, Point3D(-100,-100,-50), Point3D(100,100,-10), grid_ptr);
	add_mesh("./models/csmall.ply", matte_ptr, Point3D(27, -60, -10), Point3D(47, -30, 10), grid_ptr);
	add_mesh("./models/spider.ply", matte_ptr, Point3D(50, -70, -10), Point3D(70, -40, 10), grid_ptr);
	add_mesh("./models/hand.ply", matte_ptr, Point3D(70, -55, -10.0), Point3D(100.0, -5, 3.0), grid_ptr);
	add_mesh("./models/water.ply", matte_ptr_r, Point3D(50, -70, -10), Point3D(70, -60, 10), grid_ptr);
	add_mesh("./models/finalskull.ply", matte_ptr, Point3D(-80.0, -60, -10), Point3D(-45, 0, 5), grid_ptr);
	add_mesh("./models/water.ply", matte_ptr_r, Point3D(-80.0, -60, -10), Point3D(-45, -50, 5), grid_ptr);
	add_mesh("./models/spider.ply", matte_ptr, Point3D(-103, -65, -10), Point3D(-83, -35, 10), grid_ptr);
	add_mesh("./models/batoolnew.ply", matte_ptr, Point3D(-110, -80, -10.0), Point3D(110.0, -40, 3.0),grid_ptr);
    //Lighting
	PointLight* light_ptr = new PointLight;
    light_ptr->set_ls(40.0);
    light_ptr->set_shadows(false);
    light_ptr->set_color(red); //on table
    light_ptr->set_location(Point3D(0, -25, -5));
    add_light(light_ptr);
	//
	PointLight* light_ptr_9 = new PointLight;
    light_ptr_9->set_ls(40.0);
    light_ptr_9->set_shadows(false);
    light_ptr_9->set_color(red); //on table
    light_ptr_9->set_location(Point3D(0, -25, -5));
    add_light(light_ptr_9);
	//
	PointLight* light_ptr_7 = new PointLight;
    light_ptr_7->set_ls(40.0);
    light_ptr_7->set_shadows(true);
    light_ptr_7->set_color(red); //on table
    light_ptr_7->set_location(Point3D(27, -60, -10));
    add_light(light_ptr_7);
	//
    PointLight* light_ptr2 = new PointLight;
    light_ptr2->set_ls(20.0);
    light_ptr2->set_shadows(false);
    light_ptr2->set_color(RGBColor(1.0, 1.0, 1.0));
    light_ptr2->set_location(Point3D(0, 0, 0));
    add_light(light_ptr2);
	//
	PointLight* light_ptr3 = new PointLight;
    light_ptr3->set_ls(100);
    light_ptr3->set_shadows(true);
    light_ptr3->set_color(teal); //table
    light_ptr3->set_location(Point3D(-50, -65, -10));
    add_light(light_ptr3);
	//
	PointLight* light_pt6 = new PointLight;
    light_pt6->set_ls(40.0);
    light_pt6->set_shadows(false);
    light_pt6->set_color(RGBColor(0.0, 0.0, 1.0)); //on table
    light_pt6->set_location(Point3D(50, 50, 50));
    add_light(light_pt6);
	//directional light
	Directional* light_ptr4 = new Directional();
    light_ptr4->set_ls(50.0);
    light_ptr4->set_shadows(true);
    light_ptr4->set_color(RGBColor(0,0, 1));
    light_ptr4->set_direction(Vector3D(0, -25, -5));
    add_light(light_ptr4);

	//setting up grid cells
	grid_ptr->setup_cells();
	//adding grid pointer to geometry 
	add_geometry(grid_ptr);
}