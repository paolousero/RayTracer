
#include "AmbientOccluder.h"
#include "Sampler.h"

// ---------------------------------------------------------------------- default constructor

AmbientOccluder::AmbientOccluder (void)
	: 	Light(),
		ls(1.0),
		color(1.0)			
{}


// ---------------------------------------------------------------------- copy constructor

AmbientOccluder::AmbientOccluder (const AmbientOccluder& a)
	: 	Light(a),
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
	
	ls 		= rhs.ls;
	color 	= rhs.color;
	
	return (*this);
}


// ---------------------------------------------------------------------- destructor																			

AmbientOccluder::~AmbientOccluder (void) {}


// ---------------------------------------------------------------------- get_direction	

Vector3D								
AmbientOccluder::get_direction(ShadeRec& s) {
	return (Vector3D(0.0));
}


// ---------------------------------------------------------------------- L

RGBColor
AmbientOccluder::L(ShadeRec& sr) {	
	return (ls * color);
}

//----------------set sampler
void
	AmbientOccluder::(set_sampler(Sampler* s_ptr){
		if(sampler_ptr){
				delete sampler_ptr;
				sampler_ptr = NULL;
		}

		sampler_ptr = s_ptr;
		sampler_ptr->map_samples_to_hemisphere(1);


// ----------------------------------------------------------------------in_shadow
bool
AmbientOccluder::in_shadow(const Ray& ray, ShadeRec& s)const{
	float t = 0;
	int num_objects = s.w.objects.size();
	float d = Point3D(dir.x,dir.y,dir.z).distance(ray.o);

	for(int j = 0;j<num_objects; j++)
		if (s.w.objects[j]->shadow_hit(ray,t) && t < d)
				return (true);
	return (false);
}
