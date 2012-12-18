#include "Light.h"

#include "Constants.h"

// ---------------------------------------------------------------------- default constructor

Light::Light(void) {}

// ---------------------------------------------------------------------- dopy constructor

Light::Light(const Light& ls) {}


// ---------------------------------------------------------------------- assignment operator

Light& 
Light::operator= (const Light& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------------- destructor

Light::~Light(void) {} 



// ---------------------------------------------------------------------- L
// returns the radiance

RGBColor								
Light::L(ShadeRec& s) {
	return (black);
}

// ----------------------------------------------------------------------in_shadow
bool
Light::in_shadow(const Ray& ray, ShadeRec& s)const{
	return shadows;
}
