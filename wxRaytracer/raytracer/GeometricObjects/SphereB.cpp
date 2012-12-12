// This file contains the definition of the class sphere

#include "SphereB.h"
#include "math.h"

const double SphereB::kEpsilon = 0.001;
					
// ---------------------------------------------------------------- default constructor

SphereB::SphereB(void)	
	: 	GeometricObject(),
		center(0.0),
		radius(1.0),
		box(Point3D(center.x-radius,center.y-radius, center.z-radius),
			Point3D(center.x+radius,center.y+radius, center.z+radius))
{}


// ---------------------------------------------------------------- constructor

SphereB::SphereB(Point3D c, double r)
	: 	GeometricObject(),
		center(c),
		radius(r),
		box(c.x-r, c.y-r, c.z-r,
			c.x+r, c.y+r, c.y+r)
{}


// ---------------------------------------------------------------- clone

SphereB* 
SphereB::clone(void) const {
	return (new SphereB(*this));
}


// ---------------------------------------------------------------- copy constructor

SphereB::SphereB (const SphereB& sphere)
	: 	GeometricObject(sphere),
		center(sphere.center),
		radius(sphere.radius),
		box(sphere.center.x-sphere.radius, sphere.center.y-sphere.radius, sphere.center.z-sphere.radius,
			sphere.center.x+sphere.radius, sphere.center.y+sphere.radius, sphere.center.z+sphere.radius)
{}



// ---------------------------------------------------------------- assignment operator

SphereB& 
SphereB::operator= (const SphereB& rhs)		
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center 	= rhs.center;
	radius	= rhs.radius;

	return (*this);
}


// ---------------------------------------------------------------- destructor

SphereB::~SphereB(void) {}


//---------------------------------------------------------------- hit

bool
SphereB::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
if(box.hit(ray)){
	double 		t;
	Vector3D	temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
	
		if (t > kEpsilon) {
			tmin = t;
			sr.normal 	 = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
	
		t = (-b + e) / denom;    // larger root
	
		if (t > kEpsilon) {
			tmin = t;
			sr.normal   = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
	}
}
	return (false);
}

//----------------------------------------------------------------shadow_hit

bool
SphereB::shadow_hit(const Ray& ray, float& tmin)const
{
		double 		t;
	Vector3D	temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
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