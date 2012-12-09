#include "Disk.h"

const double Disk::kEpsilon = 0.001;

// ----------------------------------------------------------------------  default constructor

Disk::Disk(void)	
	: 	GeometricObject(),
		center(0.0),
		n(0, 1, 0),
		r(1.0)
{}


// ----------------------------------------------------------------------  constructor

Disk::Disk(const Point3D& point, const Normal& normal, const double& radius)
	:	GeometricObject(),
		center(point),
		n(normal),
		r(radius)
{
		n.normalize();
}


// ---------------------------------------------------------------- copy constructor

Disk::Disk(const Disk& disk) 
	:	GeometricObject(disk),
		center(disk.center),
		n(disk.n),
		r(disk.r)
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

	center = rhs.center;
	n = rhs.n;
	r = rhs.r;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Disk::~Disk(void)				
{}


// ----------------------------------------------------------------- hit

bool 															 
Disk::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
	float t = (center - ray.o)*n/(ray.d*n);

	if(t <=kEpsilon)
		return false;

	Point3D p = ray.o + t*ray.d;

	if(center.d_squared(p) < r*r){
		tmin = t;
		sr.normal = n;
		sr.local_hit_point = p;
		return (true);
	}

	else
		return (false);
}


// ----------------------------------------------------------------- shadow_hit
bool
Disk::shadow_hit(const Ray& ray, float& tmin) const
{
	float t = (center - ray.o)*n/(ray.d * n);

	if(t <=kEpsilon)
		return false;

	Point3D p = ray.o + t*ray.d;

	if(center.d_squared(p) < r*r){
		tmin = t;
		return (true);
	}

	else
		return (false);
}