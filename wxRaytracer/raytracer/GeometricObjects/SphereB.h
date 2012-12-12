#ifndef __SPHEREB__
#define __SPHEREB__

// This file contains the declaration of the class Sphere

#include "GeometricObject.h"
#include "BBox.h"

//-------------------------------------------------------------------------------- class Sphere

class SphereB: public GeometricObject {	
								  	
	public:
		
		SphereB(void);   									// Default constructor
				
		SphereB(Point3D center, double r);					// Constructor 
					
		SphereB(const SphereB& sphere); 						// Copy constructor
		
		virtual SphereB* 									// Virtual copy constructor
		clone(void) const;

		virtual												// Destructor
		~SphereB(void);   									

		SphereB& 											// assignment operator
		operator= (const SphereB& sphere);				
																					
		void
		set_center(const Point3D& c);
		
		void
		set_center(const double x, const double y, const double z);
		
		void
		set_radius(const double r);
						
		virtual bool 												 
		hit(const Ray& ray, double& t, ShadeRec& s) const;

		virtual bool
		shadow_hit(const Ray& ray, float& tmin)const;

		BBox
		get_bounding_box(void);
		
	private:
	
		Point3D 	center;   			// center coordinates as a point  
		double 		radius;				// the radius 
		BBox			box;
		static const double kEpsilon;   // for shadows and secondary rays
};



inline void
SphereB::set_center(const Point3D& c) {
	center = c;
}
		
inline void
SphereB::set_center(const double x, const double y, const double z) {
	center.x = x;
	center.y = y;
	center.z = z;
}
		
inline void
SphereB::set_radius(const double r) {
	radius = r;
}

inline
BBox
SphereB::get_bounding_box() {
	return BBox();
}

#endif
