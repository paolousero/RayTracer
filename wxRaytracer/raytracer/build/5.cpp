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
	int num_samples = 6;
	Sampler* sampler_ptr = new MultiJittered(num_samples);

	float ka = .2;
	float kd = .9;
	float ks = .1;
	float exp = 25;

	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_max_depth(1);
	vp.set_sampler(sampler_ptr);	

	background_color = black;

	tracer_ptr = new RayCast(this);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 5, 20);
	pinhole_ptr->set_lookat(0, 0, 0); 
	pinhole_ptr->set_view_distance(600); 
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

	PointLight* point_ptr1 = new PointLight;
	point_ptr1->set_location(0,2,2);
	point_ptr1->set_color(white);
	point_ptr1->scale_radiance(5);
	point_ptr1->set_shadows(true);
	add_light(point_ptr1);

	PointLight* point_ptr2 = new PointLight;
	point_ptr2->set_location(-1,1,-2);
	point_ptr2->set_color(red);
	point_ptr2->scale_radiance(3);
	point_ptr2->set_shadows(true);
	add_light(point_ptr2);
	
	
	PointLight* point_ptr3 = new PointLight;
	point_ptr3->set_location(1,1,-2);
	point_ptr3->set_color(blue);
	point_ptr3->scale_radiance(14);
	point_ptr3->set_shadows(true);
	add_light(point_ptr3);
	/*
	Phong* reflective_ptr1 = new Phong;
	reflective_ptr1->set_ka(0.2); 
	reflective_ptr1->set_kd(0.1); 
	reflective_ptr1->set_cd(0, .7, 0.2);  // green
	reflective_ptr1->set_ks(0.0);     
	reflective_ptr1->set_exp(1);

	Sphere* sphere_ptr1 = new Sphere(Point3D(0, .5, 0), 0.5); 	
	sphere_ptr1->set_material(reflective_ptr1);
	add_object(sphere_ptr1);
	*/

	Matte* phong_ptr1 = new Matte;
	phong_ptr1->set_ka(.7);
	phong_ptr1->set_kd(kd);
	phong_ptr1->set_cd(white);
	
	Triangle* tri1 = new Triangle(Point3D(-1,0,0),Point3D(0,0,0),Point3D(-.5,1,0));
	tri1->set_material(phong_ptr1);			
	add_object(tri1);

	Matte* phong_ptr2 = new Matte;
	phong_ptr2->set_ka(.7);
	phong_ptr2->set_kd(kd);
	phong_ptr2->set_cd(white);

	
	Triangle* tri2 = new Triangle(Point3D(.5,1,0),Point3D(0,0,0),Point3D(1,0,0));
	tri2->set_material(phong_ptr2);			
	add_object(tri2);

	Matte* phong_ptr3 = new Matte;
	phong_ptr3->set_ka(.7);
	phong_ptr3->set_kd(kd);
	phong_ptr3->set_cd(white);

	
	Triangle* tri3 = new Triangle(Point3D(-.5-.5,1,0),Point3D(.5-.5,1,0),Point3D(0-.5,2,0));
	tri3->set_material(phong_ptr3);			
	add_object(tri3);


	
	Phong* phong_ptr4 = new Phong;
	phong_ptr4->set_ka(.7);
	phong_ptr4->set_kd(kd);
	phong_ptr4->set_cd(gold);
	phong_ptr4->set_cds(gold);
	phong_ptr4->set_exp(exp);
	phong_ptr4->set_ks(ks);
	
	Disk*	disk_ptr5 = new Disk(Point3D(0,-0.5,-2),Normal(0,1,0),25); 
	disk_ptr5->set_material(phong_ptr4);			
	add_object(disk_ptr5);

	
}




