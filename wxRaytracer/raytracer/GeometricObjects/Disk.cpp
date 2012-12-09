#include "Disk.h"

const double Disk::kEpsilon = 0.001;

// ----------------------------------------------------------------------  default constructor

Disk::Disk(void)	
	: 	GeometricObject(),
		a(0.0),
		n(0, 1, 0)						
{}


// ----------------------------------------------------------------------  constructor

Disk::Disk(const Point3D& point, const Normal& normal)
	:	GeometricObject(),
		a(point),
		n(normal)
{
		n.normalize();
}


// ---------------------------------------------------------------- copy constructor

Disk::Disk(const Disk& disk) 
	:	GeometricObject(disk),
		a(disk.a),
		n(disk.n) 				
{}


// ---------------------------------------------------------------- clone

Disk* 
Disk::clone(void) const {
	return (new Disk(*this));
}


// ---------------------------------------------------------------- assignment operator

Disk& 
Disk::operator= (const Disk& rhs)	{
	
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	a = rhs.a;
	n = rhs.n;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Disk::~Disk(void)				
{}


// ----------------------------------------------------------------- hit

bool 															 
Disk::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	

	double dil = 150;
	float t = (a - ray.o) * n / (ray.d * n); 
	//float t = (0.5)*(1+sin(((ray.d.x/dil)*(ray.d.x/dil)*(ray.d.y/dil)*(ray.d.y/dil)*(180/3.14))*1.0));												
	if (t > kEpsilon) {
		tmin = t;
		sr.normal = n;
		sr.local_hit_point = ray.o + t * ray.d;
		
		return (true);	
	}

	return(false);
}


// ----------------------------------------------------------------- shadow_hit
bool
Disk::shadow_hit(const Ray& ray, float& tmin) const
{
	float t = (a - ray.o)*n/(ray.d*n);

	if(t > kEpsilon){
		tmin = t;
		return (true);
	}
	else
		return (false);
}