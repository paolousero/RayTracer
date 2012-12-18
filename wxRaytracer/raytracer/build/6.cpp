// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 5.13
// Figure 5.13(a) is rendered using the function Sampler::sample_unit_square() in Listing 5.8
// This causes the streaks on the lower part of the reflective sphere
// Figure 5.13(b) is rendered using the function Sampler::sample_unit_square() in Listing 5.13
// which removes the streaks
#include "constants.h"
void 												
World::build(void) {
	int num_samples = 1;
	Sampler* sampler_ptr = new MultiJittered(num_samples);

	float ka = .2;
	float kd = .9;
	float ks = .1;
	float exp = 25;

	vp.set_hres(900);
	vp.set_vres(350);
	vp.set_max_depth(1);
	vp.set_sampler(sampler_ptr);	

	background_color = black;

	tracer_ptr = new RayCast(this);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 5, 20);
	pinhole_ptr->set_lookat(0, 0, 0); 
	pinhole_ptr->set_view_distance(2000); 
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr); 

	/*
	AmbientOccluder* ambient_ptr = new AmbientOccluder;
	ambient_ptr->scale_radiance(5.0);
	ambient_ptr->set_sampler(new MultiJittered(256));
	set_ambient_light(ambient_ptr); 
	*/
	/*
	Ambient*  amb_ptr = new Ambient;
	amb_ptr->scale_radiance(3.);
	set_ambient_light(amb_ptr);
	*/

	Directional* point_ptr1 = new Directional;
	point_ptr1->set_direction(3,4,4);
	point_ptr1->set_color(white);
	point_ptr1->scale_radiance(1);
	point_ptr1->set_shadows(false);
	add_light(point_ptr1);

	Directional* point_ptr2 = new Directional;
	point_ptr2->set_direction(-3,4,4);
	point_ptr2->set_color(green);
	point_ptr2->scale_radiance(1);
	point_ptr2->set_shadows(false);
	add_light(point_ptr2);

	Directional* point_ptr3 = new Directional;
	point_ptr3->set_direction(0,4,-4);
	point_ptr3->set_color(white);
	point_ptr3->scale_radiance(1);
	point_ptr3->set_shadows(false);
	add_light(point_ptr3);


	
	Phong* reflective_ptr1 = new Phong;
	reflective_ptr1->set_ka(.8); 
	reflective_ptr1->set_kd(0.0); 
	reflective_ptr1->set_cd(.3, .3, 0.8);  // green
	reflective_ptr1->set_ks(0.0);     
	reflective_ptr1->set_exp(0);

	Sphere* sphere_ptr1 = new Sphere(Point3D(-3, 0, 0), 0.6); 	
	sphere_ptr1->set_material(reflective_ptr1);
	add_object(sphere_ptr1);
	
		
	Phong* reflective_ptr2 = new Phong;
	reflective_ptr2->set_ka(0); 
	reflective_ptr2->set_kd(.8); 
	reflective_ptr2->set_cd(.3, .3, 0.8);  // green
	reflective_ptr2->set_ks(0.0);     
	reflective_ptr2->set_exp(0);

	Sphere* sphere_ptr2 = new Sphere(Point3D(-1.5, 0, 0), 0.6); 	
	sphere_ptr2->set_material(reflective_ptr2);
	add_object(sphere_ptr2);

	Phong* reflective_ptr4 = new Phong;
	reflective_ptr4->set_ka(0); 
	reflective_ptr4->set_kd(0); 
	reflective_ptr4->set_cd(.3, .3, 0.8);  // green
	reflective_ptr4->set_ks(.4);     
	reflective_ptr4->set_exp(3);

	Sphere* sphere_ptr4 = new Sphere(Point3D(1.5,0, 0), 0.6); 	
	sphere_ptr4->set_material(reflective_ptr4);
	add_object(sphere_ptr4);
		
	Phong* reflective_ptr3 = new Phong;
	reflective_ptr3->set_ka(.8); 
	reflective_ptr3->set_kd(.8); 
	reflective_ptr3->set_cd(.3, .3, 0.8);  // green
	reflective_ptr3->set_ks(0.0);     
	reflective_ptr3->set_exp(0);

	Sphere* sphere_ptr3 = new Sphere(Point3D(0, 0, 0), 0.6); 	
	sphere_ptr3->set_material(reflective_ptr3);
	add_object(sphere_ptr3);
	
	Phong* reflective_ptr5 = new Phong;
	reflective_ptr5->set_ka(.8); 
	reflective_ptr5->set_kd(.8); 
	reflective_ptr5->set_cd(.3, .3, 0.8);  // green
	reflective_ptr5->set_ks(.4);     
	reflective_ptr5->set_exp(3);

	Sphere* sphere_ptr5 = new Sphere(Point3D(3, 0, 0), 0.6); 	
	sphere_ptr5->set_material(reflective_ptr5);
	add_object(sphere_ptr5);

	Matte* matte_ptr1 = new Matte;   
	matte_ptr1->set_ka(ka);	
	matte_ptr1->set_kd(kd);
	matte_ptr1->set_cd(.7,.3,.3);

	Plane* plane_ptr1 = new Plane(Point3D(0.0,-0.5,0.0), Normal(0.0,1.0,0.0));
	plane_ptr1->set_material(matte_ptr1);
	add_object(plane_ptr1);
}




