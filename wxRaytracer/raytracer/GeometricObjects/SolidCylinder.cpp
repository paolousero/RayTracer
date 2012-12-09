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
		radius(1)
{}

// ----------------------------------------------------------------------  constructor
SolidCylinder::SolidCylinder(const float bot, const float t, const float r)
	:	Compound(),
		bottom(bot),
		top(t),
		radius(r)
{
	objects.push_back(new Disk(Point3D(0, bottom, 0),
						Normal(0, -1, 0),
						radius));

	objects.push_back(new Disk(Point3D(0, bottom, 0),
						Normal(0, 1, 0),
						radius));

	objects.push_back(new OpenCylinder(bot,t,r));
}

// ---------------------------------------------------------------- copy constructor
SolidCylinder::SolidCylinder(const SolidCylinder& cyl) 
	:	Compound(cyl),
		bottom(cyl.bottom),
		top(cyl.top),
		radius(cyl.radius)
{}

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
	double point = 0.0;
	double& t = point;
	Normal normal;
	Point3D local_hit_point;
	bool hit = false;
		tmin = kHugeValue;
	int num_objects = objects.size();

	for(int j = 0;j<num_objects;j++)
		if(objects[j]->hit(ray,t,sr) && (t<tmin)){
			hit = true;
			tmin = t;
			material_ptr = objects[j]->get_material();
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
		}
		if(hit){
			sr.t=tmin;
			sr.normal = normal;
			sr.local_hit_point = local_hit_point;
		}
		return (hit);
}


// ----------------------------------------------------------------- shadow_hit
bool
SolidCylinder::shadow_hit(const Ray& ray, float& tmin) const
{
	float point = 0.0;
	float& t = point;
	Normal normal;
	Point3D local_hit_point;
	bool hit = false;
		tmin = kHugeValue;
	int num_objects = objects.size();

	for(int j = 0;j<num_objects;j++)
		if(objects[j]->shadow_hit(ray,t) && (t<tmin)){
			hit = true;
			tmin = t;
			material_ptr = objects[j]->get_material();
			//normal = sr.normal;
			//local_hit_point = sr.local_hit_point;
		}
		if(hit){
		}
		return (hit);
}

void
SolidCylinder::set_material(Material* material_ptr){
	int num_objects = objects.size();
	for(int j = 0;j<num_objects;j++)
		objects[j]->set_material(material_ptr);
}