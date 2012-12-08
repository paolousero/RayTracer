#ifndef __REFLECTIVE__
#define __REFLECTIVE__

#include "Material.h"
#include "Phong.h"
#include "Lambertian.h"
#include "PerfectSpecular.h"

class Reflective: public Phong{
public:

		Reflective(void);

		Reflective(const Reflective& m);	

		virtual Material*										
		clone(void) const;		

		Reflective& 
		operator= (const Reflective& rhs);
		//destructor-======
		~Reflective(void);

		void 													
		set_ka(const float k);
		
		void 													
		set_kd(const float k);
		
		void													
		set_cd(const RGBColor c);

		void													
		set_cds(const RGBColor c);
		
		void
		set_ks(const float ks);

		void
		set_exp(const float exp);

		void													
		set_cd(const float r, const float g, const float b);
		
		void																						
		set_cd(const float c);

		void
		set_kr(const float kr);

		void
		set_cr(const RGBColor& c);

		void
		set_cr(const float r, const float g, const float b);

	virtual RGBColor
	shade(ShadeRec& sr);

private:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
	PerfectSpecular* reflective_brdf;

};


inline void								
Reflective::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void								
Reflective::set_kd (const float kd) {
	diffuse_brdf->set_kd(kd);
}


// ---------------------------------------------------------------- set_cd

inline void												
Reflective::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

// ---------------------------------------------------------------- set_cds

inline void												
Reflective::set_cds(const RGBColor c) {
	specular_brdf->set_cd(c);
}



// ---------------------------------------------------------------- set_cd

inline void													
Reflective::set_cd(const float r, const float g, const float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

// ---------------------------------------------------------------- set_cd

inline void													
Reflective::set_cd(const float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}


// -------------------------------------------------------------- set_exp

inline void
Reflective::set_exp(const float xp) {
	specular_brdf->set_exp(xp);
}


// -------------------------------------------------------------- set_ks

inline void
Reflective::set_ks(const float k) {
	specular_brdf->set_ks(k);
}

// ---------------------------------------------------------------- set_kr

inline void													
Reflective::set_kr(const float c) {
	reflective_brdf->set_kr(c);
}

// ---------------------------------------------------------------- set_cr

inline void													
Reflective::set_cr(const RGBColor& c) {
	reflective_brdf->set_cr(c);
}

// ---------------------------------------------------------------- set_cr

inline void													
Reflective::set_cr(const float r, const float g, const float b) {
	reflective_brdf->set_cr(r,g,b);
}


#endif