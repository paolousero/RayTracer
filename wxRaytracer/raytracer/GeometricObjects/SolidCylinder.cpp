#include "SolidCylinder.h"
#include "Constants.h"
#include "Disk.h"
#include "OpenCylinder.h"

const double SolidCylinder::kEpsilon = 0.001;

// ----------------------------------------------------------------------  default constructor
SolidCylinder::SolidCylinder(void)	
	: 	Compound(),
		bottom(1),
		top(1),
		radius(1),
		box(Point3D(-1.0*radius,bottom , -1.0*radius),
			Point3D(1.0*radius,top , 1.0*radius))
{
objects.push_back(new Disk(Point3D(0, bottom, 0),
						Normal(0, -1, 0),
						radius));

	objects.push_back(new Disk(Point3D(0, top, 0),
						Normal(0, 1, 0),
						radius));

	objects.push_back(new OpenCylinder(bottom,top,radius));
}

// ----------------------------------------------------------------------  constructor
SolidCylinder::SolidCylinder(const float bot, const float t, const float r)
	:	Compound(),
		bottom(bot),
		top(t),
		radius(r),
		box(Point3D(-1.0*r,bot , -1.0*r),
			Point3D(1.0*r,t , 1.0*r))
{
	objects.push_back(new Disk(Point3D(0, bottom, 0),
						Normal(0, -1, 0),
						radius));

	objects.push_back(new Disk(Point3D(0, top, 0),
						Normal(0, 1, 0),
						radius));

	objects.push_back(new OpenCylinder(bottom,top,radius));
}

// ---------------------------------------------------------------- copy constructor
SolidCylinder::SolidCylinder(const SolidCylinder& cyl) 
	:	Compound(cyl),
		bottom(cyl.bottom),
		top(cyl.top),
		radius(cyl.radius),
		box(Point3D(-1.0*radius,bottom , -1.0*radius),
			Point3D(1.0*radius,top , 1.0*radius))

{objects.push_back(new Disk(Point3D(0, bottom, 0),
						Normal(0, -1, 0),
						radius));

	objects.push_back(new Disk(Point3D(0, top, 0),
						Normal(0, 1, 0),
						radius));

	objects.push_back(new OpenCylinder(bottom,top,radius));}

// ---------------------------------------------------------------- clone
SolidCylinder* 
SolidCylinder::clone(void) const
{
	return (new SolidCylinder(*this));
}

// ---------------------------------------------------------------- assignment operator
SolidCylinder& 
SolidCylinder::operator= (const SolidCylinder& rhs)	{
	
	if (this == &rhs)
		return (*this);

	Compound::operator= (rhs);

	bottom = rhs.bottom;
	top= rhs.top;
	radius= rhs.radius;

	return (*this);
}


// ---------------------------------------------------------------- destructor

SolidCylinder::~SolidCylinder(void)				
{}


// ----------------------------------------------------------------- hit

bool 															 
SolidCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr)const {	
if(box.hit(ray))
	return (Compound::hit(ray,tmin,sr));
else
	return (false);
}


// ----------------------------------------------------------------- shadow_hit
bool
SolidCylinder::shadow_hit(const Ray& ray, float& tmin) const
{
if(box.hit(ray))
	return (Compound::shadow_hit(ray,tmin));
else
	return (false);
}

void
SolidCylinder::set_material(Material* material_ptr){
	int num_objects = objects.size();
	for(int j = 0;j<num_objects;j++)
		objects[j]->set_material(material_ptr);
}