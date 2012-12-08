#include "PointLight.h"
#include "ShadeRec.h"

// ---------------------------------------------------------------------- default constructor

PointLight::PointLight(void) 
	: Light(),
	  ls(1.0),
	  color(1.0),
	  location(1.0,1.0,1.0)
{}

// ---------------------------------------------------------------------- copy constructor

PointLight::PointLight(const PointLight& copy) 
		: Light(copy),
		  ls(copy.ls),
		  color(copy.color),
		  location(copy.location)
{}


// ---------------------------------------------------------------------- clone

Light* 
PointLight::clone(void) const {
	return (new PointLight(*this));
}	

// ---------------------------------------------------------------------- assignment operator

PointLight& 
PointLight::operator= (const PointLight& rhs) {
	if (this == &rhs)
		return (*this);

	ls		= rhs.ls;
	color 	= rhs.color;
	location = rhs.location;

	return (*this);
}


// ---------------------------------------------------------------------- destructor

PointLight::~PointLight(void) {} 
//apparently you don't do anything else for a destructor. I guess. (Don't know if it's true or not)


// ---------------------------------------------------------------------- get the direction
Vector3D
PointLight::get_direction(ShadeRec& sr)
{
	return ((location - sr.hit_point).hat());
}


// ---------------------------------------------------------------------- L
// returns the radiance

RGBColor								
PointLight::L(ShadeRec& s) {
	return (ls * color);
}

// ----------------------------------------------------------------------in_shadow
bool
PointLight::in_shadow(const Ray& ray, ShadeRec& s)const{
	float t = 0;
	int num_objects = s.w.objects.size();
	float d = location.distance(ray.o);

	for(int j = 0;j<num_objects; j++)
		if (s.w.objects[j]->shadow_hit(ray,t) && t < d)
				return (true);
	return (false);
}

