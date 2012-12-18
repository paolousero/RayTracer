#ifndef __AMBIENTOCCLUDER__
#define __AMBIENTOCCLUDER__

#include "Light.h"
#include "Sampler.h"
#include "World.h"

class AmbientOccluder: public Light {
	public:
	
		AmbientOccluder(void);   							

		AmbientOccluder(const AmbientOccluder& a); 					 
	
		virtual Light* 									
		clone(void) const;	
		
		AmbientOccluder& 									
		operator= (const AmbientOccluder& rhs);									
		
		virtual 									
		~AmbientOccluder(void);
				
		void
		scale_radiance(const float b);
		
		void
		set_color(const float c);
		
		void
		set_color(const RGBColor& c);
		
		void
		set_color(const float r, const float g, const float b); 

		void
		set_sampler(Sampler* s_ptr);

		void
		set_min_amount(float min);
		
		virtual Vector3D								
		get_direction(ShadeRec& s); 
		
		virtual RGBColor
		L(ShadeRec& s);
	
		virtual bool
		in_shadow(const Ray& ray,const ShadeRec& sr)const;

	private:
		Vector3D u,v,w;
		Sampler* sampler_ptr;
		float min_amount;
		float		ls;
		RGBColor	color;
};



// ------------------------------------------------------------------------------- scale_radiance

inline void
AmbientOccluder::set_min_amount(float b) { 
	min_amount = b;
}



// ------------------------------------------------------------------------------- scale_radiance

inline void
AmbientOccluder::scale_radiance(const float b) { 
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
AmbientOccluder::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
AmbientOccluder::set_color(const RGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
AmbientOccluder::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}


#endif
