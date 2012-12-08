#ifndef __GLOSSYSPECULAR__
#define __GLOSSYSPECULAR__

#include "BRDF.h"

class GlossySpecular: public BRDF {
	public:
	
		GlossySpecular(void);
		
		GlossySpecular(const GlossySpecular& lamb);
		
		virtual GlossySpecular*
		clone(void) const;
		
		~GlossySpecular(void);
		
		GlossySpecular& 
		operator= (const GlossySpecular& rhs);
		
		virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
		
		virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;
			
		void
		set_ka(const float ka);	
				
		void
		set_kd(const float kd);

		void
		set_ks(const float ks);

		void
		set_exp(const float exp);
		
		void
		set_cd(const RGBColor& c);
		
		void													
		set_cd(const float r, const float g, const float b);
		
		void													
		set_cd(const float c);
					
	private:
		float		ks;
		float		kd;
		float		exp;
		RGBColor 	cd;

};




// -------------------------------------------------------------- set_ka

inline void
GlossySpecular::set_ka(const float k) {
	kd = k;
}


// -------------------------------------------------------------- set_kd

inline void
GlossySpecular::set_kd(const float k) {
	kd = k;
}

// -------------------------------------------------------------- set_exp

inline void
GlossySpecular::set_exp(const float xp) {
	exp = xp;
}


// -------------------------------------------------------------- set_ks

inline void
GlossySpecular::set_ks(const float k) {
	ks = k;
}

// -------------------------------------------------------------- set_cd

inline void
GlossySpecular::set_cd(const RGBColor& c) {
	cd = c;
}


// ---------------------------------------------------------------- set_cd

inline void													
GlossySpecular::set_cd(const float r, const float g, const float b) {
	cd.r = r; cd.g = g; cd.b = b;
}


// ---------------------------------------------------------------- set_cd

inline void													
GlossySpecular::set_cd(const float c) {
	cd.r = c; cd.g = c; cd.b = c;
}

#endif
