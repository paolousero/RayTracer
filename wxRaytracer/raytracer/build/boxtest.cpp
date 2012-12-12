//Testing BBox

void 												
World::build(void) {
	int num_samples = 1; 
	
	// view plane  
	RGBColor white(1.0);
	RGBColor green(0,.5,0);
	RGBColor red(.8,0,0);
	RGBColor lightblue(0.8,0.8,1.0);

	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(1.0);
	vp.set_samples(num_samples);
	
	// the ambient light here is the same as the default set in the World
	// constructor, and can therefore be left out
	/*
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr); 
	*/

	background_color = black;			// default color - this can be left out
	
	//tracer_ptr = new RayCast(this); 
	tracer_ptr = new Whitted(this);

	
	// camera
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 2, 6); 
	pinhole_ptr->set_lookat(0,0,0);
	pinhole_ptr->set_view_distance(300.0);
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);

	
	// light
	PointLight* point_ptr1 = new PointLight;
	point_ptr1->set_location(0,4.3,2.0);
	point_ptr1->set_color(white);
	point_ptr1->scale_radiance(10);
	point_ptr1->set_shadows(true);
	add_light(point_ptr1);

	//objects
	float ka = .2;
	float kd = .9;
	float ks = .1;
	float exp = 25;

	/*
	Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(0.25);
	reflective_ptr1->set_kd(.5);
	reflective_ptr1->set_cd(yellow);
	reflective_ptr1->set_cds(yellow);
	reflective_ptr1->set_exp(100);
	reflective_ptr1->set_kr(0.75);
	reflective_ptr1->set_cr(white);
	*/
	Phong* phong_ptr4 = new Phong;
	phong_ptr4->set_ka(.7);
	phong_ptr4->set_kd(kd);
	phong_ptr4->set_cd(red);
	phong_ptr4->set_cds(red);
	phong_ptr4->set_exp(exp);
	phong_ptr4->set_ks(ks);

	SolidCylinder* sphere_ptr = new SolidCylinder(-1.3,1.3,1.3);
	sphere_ptr->set_material(phong_ptr4);
	add_object(sphere_ptr);
	
	Matte* matte_ptr1 = new Matte;   
	matte_ptr1->set_ka(ka);	
	matte_ptr1->set_kd(kd);
	matte_ptr1->set_cd(white);

	Plane* plane_ptr1 = new Plane(Point3D(0.0,-2,0.0), Normal(0.0,1.0,0.0));
	plane_ptr1->set_material(matte_ptr1);
	add_object(plane_ptr1);

	Phong* phong_ptr5 = new Phong;
	phong_ptr5->set_ka(.7);
	phong_ptr5->set_kd(kd);
	phong_ptr5->set_cd(red);
	phong_ptr5->set_cds(red);
	phong_ptr5->set_exp(exp);
	phong_ptr5->set_ks(ks);


	Sphere* sphere_ptr2 = new Sphere(Point3D(2,0,0),1.0);
	sphere_ptr2->set_material(phong_ptr5);
	add_object(sphere_ptr2);

}
