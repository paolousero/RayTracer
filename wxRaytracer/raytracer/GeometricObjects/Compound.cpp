#include "Compound.h"
#include "Constants.h"


const double Compound::kEpsilon = 0.001;

// ----------------------------------------------------------------------  default constructor
Compound::Compound(void)	
	: 	GeometricObject(),
		objects()
{}

// ----------------------------------------------------------------------  constructor
Compound::Compound(std::vector<GeometricObject*>& ob)
	:	GeometricObject(),
		objects(ob)
{}

// ---------------------------------------------------------------- copy constructor
Compound::Compound(const Compound& comp) 
	:	GeometricObject(comp),
		objects(comp.objects)
{}

// ---------------------------------------------------------------- clone
Compound* 
Compound::clone(void) const
{
	return (new Compound(*this));
}

// ---------------------------------------------------------------- assignment operator
Compound& 
Compound::operator= (const Compound& rhs)	{
	
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	objects = rhs.objects;

	return (*this);
}


// ---------------------------------------------------------------- destructor

Compound::~Compound(void)				
{}


// ----------------------------------------------------------------- hit

bool 															 
Compound::hit(const Ray& ray, double& tmin, ShadeRec& sr)const {	
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
Compound::shadow_hit(const Ray& ray, float& tmin) const
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
Compound::set_material(Material* material_ptr){
	int num_objects = objects.size();
	for(int j = 0;j<num_objects;j++)
		objects[j]->set_material(material_ptr);
}