#ifndef __OPENCYLINDER__
#define __OPENCYLINDER__

// This file contains the declaration of the class Sphere

#include "GeometricObject.h"

//-------------------------------------------------------------------------------- class Sphere

class OpenCylinder: public GeometricObject {	
								  	
	public:
		
		OpenCylinder(void);   									// Default constructor
				
		OpenCylinder( float bottom, float top, float radius);					// Constructor 
					
		OpenCylinder(const OpenCylinder& cyl); 						// Copy constructor
		
		virtual OpenCylinder* 									// Virtual copy constructor
		clone(void) const;

		virtual												// Destructor
		~OpenCylinder(void);   									

		OpenCylinder& 											// assignment operator
		operator= (const OpenCylinder& cyl);				
		
		void
		set_radius(const double r);
						
		virtual bool 												 
		hit(const Ray& ray, double& t, ShadeRec& s) const;

		virtual bool
		shadow_hit(const Ray& ray, float& tmin)const;
		
	protected:
	
float bottom;
float top;
float radius;
		
		static const double kEpsilon;   // for shadows and secondary rays
};
		
inline void
OpenCylinder::set_radius(const double r) {
	radius = r;
}

#endif
