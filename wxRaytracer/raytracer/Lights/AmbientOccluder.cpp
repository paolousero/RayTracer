
#include "AmbientOccluder.h"
#include "Sampler.h"

// ---------------------------------------------------------------------- default constructor

AmbientOccluder::AmbientOccluder (void)
	: 	Light(),
		w(0),
		u(0),
		v(0),
		sampler_ptr(new Regular(1)),
		min_amount(0.000001),
		ls(1.0),
		color(.9,.9,.9)			
{}


// ---------------------------------------------------------------------- copy constructor

AmbientOccluder::AmbientOccluder (const AmbientOccluder& a)
	: 	Light(a),
		w(a.w),
		u(a.u),
		v(a.v),
		sampler_ptr(a.sampler_ptr),
		min_amount(a.min_amount),
		ls(a.ls),
		color(a.color) 		
{}


// ---------------------------------------------------------------------- clone

Light* 
AmbientOccluder::clone(void) const {
	return (new AmbientOccluder(*this));
}	


// ---------------------------------------------------------------------- assignment operator

AmbientOccluder& 
AmbientOccluder::operator= (const AmbientOccluder& rhs) {
	if (this == &rhs)
		return (*this);
			
	Light::operator= (rhs);
	w = rhs.w;
	v = rhs.v;
	u = rhs.u;
	sampler_ptr = rhs.sampler_ptr;
	min_amount = rhs.min_amount;
	ls 		= rhs.ls;
	color 	= rhs.color;
	
	return (*this);
}


// ---------------------------------------------------------------------- destructor																			

AmbientOccluder::~AmbientOccluder (void) {}


// ---------------------------------------------------------------------- get_direction	

Vector3D								
AmbientOccluder::get_direction(ShadeRec& s) {
	Point3D sp = sampler_ptr->sample_hemisphere();
	return (sp.x*u+sp.y*v+sp.z*w);
}


// ---------------------------------------------------------------------- L

RGBColor
AmbientOccluder::L(ShadeRec& sr) {	
	w = sr.normal;
	//jitter up vector in case normal is vertical
	v = w ^ Vector3D(0.0072, 1.0, 0.0034);
	v.normalize();
	u = v ^ w;

	Ray shadow_ray;
	shadow_ray.o = sr.hit_point;
	shadow_ray.d = get_direction(sr);

	if(in_shadow(shadow_ray, sr))
			return (min_amount * ls * color);
	else
		return (ls * color);
}

//----------------set sampler
void
	AmbientOccluder::set_sampler(Sampler* s_ptr){
		if(sampler_ptr){
			//	delete sampler_ptr;
				sampler_ptr = NULL;
		}

		sampler_ptr = s_ptr;
		sampler_ptr->map_samples_to_hemisphere(1);
}

// ----------------------------------------------------------------------in_shadow
bool
AmbientOccluder::in_shadow(const Ray& ray,const ShadeRec& sr)const{
	float t;
	int num_objects = sr.w.objects.size();


	for(int j = 0;j<num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray,t))
				return (true);
	return (false);
}
