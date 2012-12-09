#ifndef __COMPOUND__
#define __COMPOUND__

#include "GeometricObject.h"
#include <vector>

class Compound: public GeometricObject
{
public:
		Compound(void);   												// default constructor
		
		Compound(std::vector<GeometricObject*>& objects);			// constructor	
	
		Compound(const Compound& compound); 									// copy constructor
		
		virtual Compound* 												// virtual copy constructor
		clone(void)const;

		Compound& 														// assignment operator
		operator= (const Compound& rhs);	
		
		virtual														// destructor
		~Compound(void);   											
					
		virtual bool 																								 
		hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

		virtual bool
		shadow_hit(const Ray& ray, float& tmin)const;
		
		void
		add_object(GeometricObject* object_ptr);

		void
		set_material(Material* material_ptr);

	protected:
	
		std::vector<GeometricObject*> objects;

		static const double kEpsilon;   // for shadows and secondary rays
};


inline void
Compound::add_object(GeometricObject* object_ptr)
{
	objects.push_back(object_ptr);

}


#endif