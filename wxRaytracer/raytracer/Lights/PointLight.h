
#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include "Light.h"

#include "Vector3D.h"
#include "RGBColor.h"
#include "Ray.h"

#include "World.h"
#include "ShadeRec.h"

//-------------------------------------------------------------------- class Light

class PointLight: public Light{	
	public:
	
		PointLight(void);
								
		PointLight(const PointLight& pl);			

		PointLight& 								
		operator= (const PointLight& rhs); 

		virtual Light* 						
		clone(void) const;
		
		virtual 							
		~PointLight(void);

		void
		scale_radiance(const float b);
		
		void
		set_color(const float c);
		
		void
		set_color(const RGBColor& c);
		
		void
		set_color(const float r, const float g, const float b); 	

		void
		set_location(Point3D d);						
		
		void
		set_location(float dx, float dy, float dz);
						
		virtual Vector3D								
		get_direction(ShadeRec& sr);				
																
		virtual RGBColor														
		L(ShadeRec& sr);

		virtual bool
		in_shadow(const Ray& ray, ShadeRec& sr)const;

	private:

		float ls;
		RGBColor color;
		Point3D location;
};


// inlined access functions


// ------------------------------------------------------------------------------- scale_radiance

inline void
PointLight::scale_radiance(const float b) { 
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const RGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
PointLight::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

// ---------------------------------------------------------------------- set_direction

inline void
PointLight::set_location(Point3D d) {
	location = d;
}


// ---------------------------------------------------------------------- set_direction 

inline void
PointLight::set_location(float dx, float dy, float dz) {
	location.x = dx; location.y = dy; location.z = dz;
}

#endif

