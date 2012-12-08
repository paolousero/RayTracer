#include "PerfectSpecular.h"
#include "Constants.h"

// ---------------------------------------------------------------------- default constructor

PerfectSpecular::PerfectSpecular(void) 
		:BRDF(),
		kr(0.5),
		cr(0.5),
		kd(0.5),
		ks(0.5),
		cd(0.5),
		exp(2.0)
{}


// ---------------------------------------------------------------------- copy constructor

PerfectSpecular::PerfectSpecular(const PerfectSpecular& lamb) 
	:   BRDF(lamb),
		kd(lamb.kd), 
		cd(lamb.cd),
		ks(lamb.ks),
		exp(lamb.exp)
{}

// ---------------------------------------------------------------------- clone

PerfectSpecular* 
PerfectSpecular::clone(void) const {
	return (new PerfectSpecular(*this));
}	


// ---------------------------------------------------------------------- destructor

PerfectSpecular::~PerfectSpecular(void) {}


// ---------------------------------------------------------------------- assignment operator
PerfectSpecular& 
PerfectSpecular::operator= (const PerfectSpecular& rhs) {
	if (this == &rhs)
		return (*this);
		
	BRDF::operator= (rhs);
	
	kd = rhs.kd; 
	cd = rhs.cd;
	ks = rhs.ks;
	exp = rhs.exp;

	return (*this);
}

// ---------------------------------------------------------------------- sample_f
RGBColor
PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const{
	float ndotwo = sr.normal * wo;
	wi = -wo + 2.0*sr.normal*ndotwo;

	return (kr*cr/(sr.normal*wi));
}
// ---------------------------------------------------------------------- f
RGBColor
PerfectSpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
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
PerfectSpecular::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (kd * cd);
}