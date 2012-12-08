#ifndef __PHONG__
#define __PHONG__

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

class Phong: public Material{
	public:
		Phong(void);

		Phong(const Phong& m);	

		virtual Material*										
		clone(void) const;		

		Phong& 
		operator= (const Phong& rhs);
		//destructor-======
		~Phong(void);

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

		virtual RGBColor
		shade(ShadeRec& s);

protected:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
	GlossySpecular* specular_brdf;
};


// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void								
Phong::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void								
Phong::set_kd (const float kd) {
	diffuse_brdf->set_kd(kd);
}


// ---------------------------------------------------------------- set_cd

inline void												
Phong::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

// ---------------------------------------------------------------- set_cds

inline void												
Phong::set_cds(const RGBColor c) {
	specular_brdf->set_cd(c);
}



// ---------------------------------------------------------------- set_cd

inline void													
Phong::set_cd(const float r, const float g, const float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

// ---------------------------------------------------------------- set_cd

inline void													
Phong::set_cd(const float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}


// -------------------------------------------------------------- set_exp

inline void
Phong::set_exp(const float xp) {
	specular_brdf->set_exp(xp);
}


// -------------------------------------------------------------- set_ks

inline void
Phong::set_ks(const float k) {
	specular_brdf->set_ks(k);
}


#endif