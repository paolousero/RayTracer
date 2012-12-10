// This file contains the definition of the class sphere

#include "OpenCylinder.h"
#include "math.h"

const double OpenCylinder::kEpsilon = 0.001;
					
// ---------------------------------------------------------------- default constructor

OpenCylinder::OpenCylinder(void)	
	: 	GeometricObject(),
		bottom(1.0),
		top(1.0),
		radius(1.0)
{}


// ---------------------------------------------------------------- constructor

OpenCylinder::OpenCylinder(float b, float t, float r)
	: 	GeometricObject(),
		bottom(b),
		top(t),
		radius(r)
{}


// ---------------------------------------------------------------- clone

OpenCylinder* 
OpenCylinder::clone(void) const {
	return (new OpenCylinder(*this));
}


// ---------------------------------------------------------------- copy constructor

OpenCylinder::OpenCylinder (const OpenCylinder& cyl)
	: 	GeometricObject(cyl),
		bottom(cyl.bottom),
		top(cyl.top),
		radius(cyl.radius)
{}



// ---------------------------------------------------------------- assignment operator

OpenCylinder& 
OpenCylinder::operator= (const OpenCylinder& rhs)		
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	top 	= rhs.top;
	bottom 	= rhs.bottom;
	radius	= rhs.radius;

	return (*this);
}


// ---------------------------------------------------------------- destructor

OpenCylinder::~OpenCylinder(void) {}


//---------------------------------------------------------------- hit

bool
OpenCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double 		t;
	double		y;
	//Vector3D	temp 	= ray.o - center;
	double 		a 		= (ray.d.x*ray.d.x) + (ray.d.z*ray.d.z);
	double 		b 		= 2.0 *(ray.o.x*ray.d.x + ray.o.z*ray.d.z);
	double 		c 		= (ray.o.x*ray.o.x) + (ray.o.z*ray.o.z) - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;
	Normal norm = Normal(sr.hit_point.x/radius*1.0,0,sr.hit_point.z/radius*1.0);
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		y = ray.o.y+t*ray.d.y;

		if(t > kEpsilon && bottom<y<top) {
			tmin = t;
			sr.local_hit_point = ray.o + t * ray.d;
			sr.normal 	= norm;
			return (true);
		} 
	
		t = (-b + e) / denom;    // larger root
		y = ray.o.y+t*ray.d.y;

		if(t > kEpsilon&& bottom<y<top) {
			tmin = t;
			
			sr.local_hit_point = ray.o + t * ray.d;
			sr.normal   =  norm;
			return (true);
		} 
	}

	return (false);
}

//----------------------------------------------------------------shadow_hit

bool
OpenCylinder::shadow_hit(const Ray& ray, float& tmin)const
{
	double 		t;
	//Vector3D	temp 	= ray.o - center;
	double 		a 		= (ray.d.x*ray.d.x) + (ray.d.z*ray.d.z);
	double 		b 		= 2.0 *(ray.o.x*ray.d.x + ray.o.z*ray.d.z);
	double 		c 		= (ray.o.x*ray.o.x) + (ray.o.z*ray.o.z) - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
	
		if (t > kEpsilon) {
			tmin = t;
			//sr.normal 	 = (temp + t * ray.d) / radius;
			//sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
	
		t = (-b + e) / denom;    // larger root
	
		if (t > kEpsilon) {
			tmin = t;
			//sr.normal   = (temp + t * ray.d) / radius;
			//sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
	}

	return (false);
}