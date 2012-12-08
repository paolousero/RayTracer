#include "GlossySpecular.h"
#include "Constants.h"

// ---------------------------------------------------------------------- default constructor

GlossySpecular::GlossySpecular(void) 
		:BRDF(),
		kd(0.5),
		ks(0.5),
		cd(0.5),
		exp(15.0)
{}


// ---------------------------------------------------------------------- copy constructor

GlossySpecular::GlossySpecular(const GlossySpecular& lamb) 
	:   BRDF(lamb),
		kd(lamb.kd), 
		cd(lamb.cd),
		ks(lamb.ks),
		exp(lamb.exp)
{}

// ---------------------------------------------------------------------- clone

GlossySpecular* 
GlossySpecular::clone(void) const {
	return (new GlossySpecular(*this));
}	


// ---------------------------------------------------------------------- destructor

GlossySpecular::~GlossySpecular(void) {}


// ---------------------------------------------------------------------- assignment operator
GlossySpecular& 
GlossySpecular::operator= (const GlossySpecular& rhs) {
	if (this == &rhs)
		return (*this);
		
	BRDF::operator= (rhs);
	
	kd = rhs.kd; 
	cd = rhs.cd;
	ks = rhs.ks;
	exp = rhs.exp;

	return (*this);
}

// ---------------------------------------------------------------------- f
RGBColor
GlossySpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	RGBColor L;
	float ndotwi = sr.normal * wi;
	Vector3D r( -wi + 2.0 * sr.normal *ndotwi);
	float rdotwo = r * wo;
	
	if(rdotwo>0)
		L = ks * std::pow(rdotwo, exp);
	return (L);
}


// ---------------------------------------------------------------------- rho

RGBColor
GlossySpecular::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (kd * cd);
}


