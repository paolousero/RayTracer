#ifndef __DISK__
#define __DISK__

#include "GeometricObject.h"

//-------------------------------------------------------------------- class Disk
class Disk: public GeometricObject {
	
	public:
	
		Disk(void);   												// default constructor
		
		Disk(const Point3D& point, const Normal& normal);			// constructor	
	
		Disk(const Disk& disk); 									// copy constructor
		
		virtual Disk* 												// virtual copy constructor
		clone(void) const;

		Disk& 														// assignment operator
		operator= (const Plane& rhs);	
		
		virtual														// destructor
		~Disk(void);   											
					
		virtual bool 																								 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		virtual bool
		shadow_hit(const Ray& ray, float& tmin)const;
		
	private:
	
		Point3D 	a;   				// point through which plane passes 
		Normal 		n;					// normal to the plane
				
		static const double kEpsilon;   // for shadows and secondary rays
};

#endif
