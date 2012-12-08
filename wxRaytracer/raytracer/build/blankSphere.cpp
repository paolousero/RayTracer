void 												
World::build(void) {
	int num_samples = 1; 
	
	// view plane  
	  
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(0.5);
	vp.set_samples(num_samples);

	
	// the ambient light here is the same as the default set in the World
	// constructor, and can therefore be left out
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr); 
	
	background_color = black;			// default color - this can be left out
	
	tracer_ptr = new RayCast(this); 
	//tracer_ptr = new MultipleObjects(this);

	
	// camera
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 500); 
	pinhole_ptr->set_lookat(0.0);
	pinhole_ptr->set_view_distance(600.0);
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);

	//bounding box
	//BBox* bbox_ptr = new BBox;
	
	
	// light
	
	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(100, 100, 200);
	light_ptr1->scale_radiance(1.0); 	
	add_light(light_ptr1);
	
	RGBColor white(1.0);
	
	float ka = 1.00;
	float kd = 1.00;

	//Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 0, 1));
	//plane_ptr->set_color(1.0, 1.0, 1.0);	// dark green
	//add_object(plane_ptr);

	Matte* matte_ptr1 = new Matte;   
	matte_ptr1->set_ka(ka);	
	matte_ptr1->set_kd(kd);
	matte_ptr1->set_cd(white);	

	Sphere*	sphere_ptr = new Sphere(Point3D(0, 0, -200), 60); 
	sphere_ptr->set_material(matte_ptr1);						
	add_object(sphere_ptr);
}
