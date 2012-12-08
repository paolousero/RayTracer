#include "Reflective.h"
#include "Material.h"
#include "PerfectSpecular.h"

// ---------------------------------------------------------------- default constructor

Reflective::Reflective (void)
	:	Phong(),
		ambient_brdf(new Lambertian),
		diffuse_brdf(new Lambertian),
		reflective_brdf(new PerfectSpecular)
{}

// ---------------------------------------------------------------- copy constructor

Reflective::Reflective(const Reflective& m)
	: 	Phong(m)
{
	if(m.ambient_brdf)
		ambient_brdf = m.ambient_brdf->clone(); 
	else  ambient_brdf = NULL;
	
	if(m.diffuse_brdf)
		diffuse_brdf = m.diffuse_brdf->clone(); 
	else  diffuse_brdf = NULL;

	if(m.reflective_brdf)
		reflective_brdf = m.reflective_brdf->clone(); 
	else  reflective_brdf = NULL;
}

// ---------------------------------------------------------------- clone

Material*										
Reflective::clone(void) const {
	return (new Reflective(*this));
}	

// ---------------------------------------------------------------- destructor

Reflective::~Reflective(void) {

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
}


// ---------------------------------------------------------------- shade

RGBColor
Reflective::shade(ShadeRec& sr)
{
	RGBColor L(Phong::shade(sr));

	Vector3D wo =  -sr.ray.d;
	Vector3D wi;
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
	Ray reflected_ray(sr.hit_point, wi);

	L += fr*sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth+1)*(sr.normal*wi);

	return (L);
}