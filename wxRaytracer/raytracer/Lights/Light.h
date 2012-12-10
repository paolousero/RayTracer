#ifndef __LIGHT__
#define __LIGHT__

#include "Vector3D.h"
#include "RGBColor.h"
#include "Ray.h"

class ShadeRec;


//-------------------------------------------------------------------- class Light

class Light {	
	public:
	
		Light(void);
								
		Light(const Light& ls);			

		Light& 								
		operator= (const Light& rhs); 

		virtual Light* 						
		clone(void) const = 0;
		
		virtual 							
		~Light(void);
						
		virtual Vector3D								
		get_direction(ShadeRec& sr) = 0;				
																
		virtual RGBColor														
		L(ShadeRec& sr);


		virtual void
		set_shadows(bool s);

		virtual bool
		casts_shadows(void);

		virtual bool
		in_shadow(const Ray& ray, ShadeRec& sr)const;

protected:
	bool shadows;
};


inline void
Light::set_shadows(bool s){
	shadows = s;
}

inline bool
Light::casts_shadows(){
	return true;
}

#endif