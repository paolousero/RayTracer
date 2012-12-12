#ifndef __CYLINDER__
#define __CYLINDER__

#include "Compound.h"
#include "BBox.h"
#include <vector>

class SolidCylinder: public Compound
{
public:
		SolidCylinder(void);   												// default constructor
		
		SolidCylinder(const float bottom, const float top, const float radius);			// constructor	
	
		SolidCylinder(const SolidCylinder& cc); 									// copy constructor
		
		virtual SolidCylinder* 												// virtual copy constructor
		clone(void)const;

		SolidCylinder& 														// assignment operator
		operator= (const SolidCylinder& rhs);	
		
		virtual														// destructor
		~SolidCylinder(void);   											
					
		virtual bool 																								 
		hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

		virtual bool
		shadow_hit(const Ray& ray, float& tmin)const;
		
		void
		add_object(GeometricObject* object_ptr);

		void
		set_material(Material* material_ptr);

		BBox
		get_bounding_box(void);

	private:
	
		float bottom;
		float top;
		float radius;
		BBox			box;
		static const double kEpsilon;   // for shadows and secondary rays
};


inline void
SolidCylinder::add_object(GeometricObject* object_ptr)
{
	objects.push_back(object_ptr);

}

inline
BBox
SolidCylinder::get_bounding_box() {
	return box;
}

#endif