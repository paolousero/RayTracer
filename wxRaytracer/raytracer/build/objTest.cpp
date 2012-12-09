#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include "Point3D.h"
#include "constants.h"
//#include "ObjReaderd.h"
using namespace std;


void 												
World::build(void) {

		//////////////////========================================
	
		string current2;
		vector<Point3D> verts2;
		vector<vector<Point3D>> faces2;
		int vertNum2 = 0;
		int faceNum2 = 0;
		int vertInFace2;

		ifstream objFile2 ("vox.obj");

		if(!objFile2){
			//cout<<"There is an error.";
		}
		else if(objFile2.is_open())
		{
			while(objFile2.good()){
				getline(objFile2,current2);
				//Vertex stuff = = = = = = = = = = = = = = = 
				if(current2.substr(0,2)=="v ")
				{
					verts2.push_back(Point3D());

					istringstream s(current2.substr(2));
					s >> verts2[vertNum2].x;
					s >> verts2[vertNum2].y;
					s >> verts2[vertNum2].z;

				//	cout<<verts[vertNum].x<<endl;
				//	cout<<verts[vertNum].y<<endl;
				//	cout<<verts[vertNum].z<<endl;
				//	cout<<endl;

					vertNum2++;
				}
				//Face stuff = = = = = = = = = = = = = = = 
				else if(current2.substr(0,2)=="f ")
				{
					faces2.push_back(vector<Point3D>());

					string temp;
					istringstream s(current2.substr(2));
					//temp = temp.substr(0,1);
						//vertInFace = atoi(temp.c_str())-1;
						//there are still tokens in the current face line, 
						//keep parsing s and extracting verts.
					    //onst char* t = temp[0];
						//int x = atoi(t);
						//cout<<faces[faceNum].back();
					while(s.good())
					{
						s >> temp;
						
						char *copy = strdup(temp.c_str());
						vertInFace2 = atoi(strtok(copy, "/"));


						faces2[faceNum2].push_back(verts2[vertInFace2-1]);


					}
					faceNum2++;	
				}
			}
		}	
		
	//////////////////========================================

	int num_samples = 5; 
	
	// view plane  
	  
	RGBColor white(1.0);
	RGBColor green(0,.5,0);
	RGBColor red(.8,0,0);
	RGBColor lightblue(0.8,0.8,1.0);

	vp.set_hres(500);
	vp.set_vres(500);
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
	pinhole_ptr->set_eye(0, 2, 5); 
	pinhole_ptr->set_lookat(0.0);
	pinhole_ptr->set_view_distance(600.0);
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);

	
	// light
	/*
	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(100, 100, 100);
	light_ptr1->set_color(white);
	light_ptr1->scale_radiance(4); 	
	add_light(light_ptr1);
	
	
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction(-100, -100, 100);
	light_ptr2->set_color(red);
	light_ptr2->scale_radiance(4); 	
	add_light(light_ptr2);
	*/
	PointLight* point_ptr1 = new PointLight;
	point_ptr1->set_location(0,1,0);
	point_ptr1->set_color(white);
	point_ptr1->scale_radiance(5);
	point_ptr1->set_shadows(true);
	add_light(point_ptr1);

	//objects
	float ka = .2;
	float kd = .9;
	float ks = .1;
	float exp = 25;
	

	Phong* phong_ptr1 = new Phong;
	phong_ptr1->set_ka(.7);
	phong_ptr1->set_kd(kd);
	phong_ptr1->set_cd(yellow);
	phong_ptr1->set_cds(yellow);
	phong_ptr1->set_exp(exp);
	phong_ptr1->set_ks(ks);

	
	Vector3D a = Vector3D(1,0,1);
	Vector3D b = Vector3D(1,1,1); 
	Vector3D c = Vector3D(2,0,-2); 
	
	Triangle*	triangle_ptr1 = new Triangle(a,b,c); 
	triangle_ptr1->set_material(phong_ptr1);			
	add_object(triangle_ptr1);

	
	Phong* phong_ptr2 = new Phong;
	phong_ptr2->set_ka(.7);
	phong_ptr2->set_kd(kd);
	phong_ptr2->set_cd(green);
	phong_ptr2->set_cds(green);
	phong_ptr2->set_exp(exp);
	phong_ptr2->set_ks(ks);

	
	 a = Vector3D(-5,0,-8);
	b = Vector3D(5,0,-8); 
	c = Vector3D(0,5,-8); 
	
	Triangle*	triangle_ptr5 = new Triangle(a,b,c); 
	triangle_ptr5->set_material(phong_ptr2);			
	add_object(triangle_ptr5);

		Reflective* reflective_ptr1 = new Reflective;
		reflective_ptr1->set_ka(0.25);
		reflective_ptr1->set_kd(.5);
		reflective_ptr1->set_cd(yellow);
		reflective_ptr1->set_cds(yellow);
		reflective_ptr1->set_exp(100);
		reflective_ptr1->set_kr(0.75);
		reflective_ptr1->set_cr(white);

	Sphere* sphere_ptr = new Sphere(Point3D(-0.5,0.5,0), .3);
	sphere_ptr->set_material(reflective_ptr1);
	add_object(sphere_ptr);

	
		for(int x =0;x<faces2.size();x++)
		{
			/*
		Phong* phong_ptr3 = new Phong;
		phong_ptr3->set_ka(ka);
		phong_ptr3->set_kd(kd);
		phong_ptr3->set_cd(lightblue);
		phong_ptr3->set_cds(white);
		phong_ptr3->set_exp(exp);
		phong_ptr3->set_ks(ks);
		*/

			Reflective* reflective_ptr2 = new Reflective;
		reflective_ptr2->set_ka(0.25);
		reflective_ptr2->set_kd(.5);
		reflective_ptr2->set_cd(yellow);
		reflective_ptr2->set_cds(yellow);
		reflective_ptr2->set_exp(100);
		reflective_ptr2->set_kr(0.75);
		reflective_ptr2->set_cr(white);
		faces2[x][0].z -=5;
		faces2[x][1].z -=5;
		faces2[x][2].z -=5;

		Triangle*	triangle_ptr2 = new Triangle(faces2[x][0],faces2[x][1],faces2[x][2]); 
		//Triangle*	triangle_ptr = new Triangle(a,b,c); 
		triangle_ptr2->set_material(reflective_ptr2);			// light purple
		add_object(triangle_ptr2);
		}
		
		Matte* matte_ptr1 = new Matte;   
		matte_ptr1->set_ka(ka);	
		matte_ptr1->set_kd(kd);
		matte_ptr1->set_cd(white);

		Plane* plane_ptr1 = new Plane(Point3D(0.0,0.0,0.0), Normal(0.0,1.0,0.0));
		plane_ptr1->set_material(matte_ptr1);
		add_object(plane_ptr1);
}
