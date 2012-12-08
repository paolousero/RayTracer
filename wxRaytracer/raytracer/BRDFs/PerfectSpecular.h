#ifndef __PERFECTSPECULAR__
#define __PERFECTSPECULAR__

#include "BRDF.h"

class PerfectSpecular: public BRDF {
	public:
	
		PerfectSpecular(void);
		
		PerfectSpecular(const PerfectSpecular& lamb);
		
		virtual PerfectSpecular*
		clone(void) const;
		
		~PerfectSpecular(void);
		
		PerfectSpecular& 
		operator= (const PerfectSpecular& rhs);
		
		virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;

		virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
		
		virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;
			
		void
		set_cr(const float cr);	
				
		void
		set_kd(const float kd);

		void
		set_exp(const float exp);
		
		void
		set_cd(const RGBColor& c);
		
		void													
		set_cd(const float r, const float g, const float b);
		
		void													
		set_cd(const float c);

		void
		set_kr(const float kr);

		void
		set_cr(const RGBColor& b);

		void
		set_cr(const float r, const float g, const float b);

	private:
		float		kr;
		RGBColor	cr;
		float		ks;
		float		kd;
		float		exp;
		RGBColor 	cd;

};




// -------------------------------------------------------------- set_ka

inline void
PerfectSpecular::set_cr(const float k) {
	cr = k;
}


// -------------------------------------------------------------- set_kd

inline void
PerfectSpecular::set_kd(const float k) {
	kd = k;
}

// -------------------------------------------------------------- set_exp

inline void
PerfectSpecular::set_exp(const float xp) {
	exp = xp;
}


// -------------------------------------------------------------- set_ks

inline void
PerfectSpecular::set_kr(const float k) {
	kr = k;
}

// -------------------------------------------------------------- set_cd

inline void
PerfectSpecular::set_cd(const RGBColor& c) {
	cd = c;
}


// ---------------------------------------------------------------- set_cd

inline void													
PerfectSpecular::set_cd(const float r, const float g, const float b) {
	cd.r = r; cd.g = g; cd.b = b;
}


// ---------------------------------------------------------------- set_cd

inline void													
PerfectSpecular::set_cd(const float c) {
	cd.r = c; cd.g = c; cd.b = c;
}



// ---------------------------------------------------------------- set_cr

inline void													
PerfectSpecular::set_cr(const RGBColor& c) {
	cr = c;
}

// ---------------------------------------------------------------- set_cr

inline void													
PerfectSpecular::set_cr(const float r, const float g, const float b) {
	cr.r = r; cr.g = g; cr.b = b;
}
#endif
