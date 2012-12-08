#ifndef __TORUS__
#define __TORUS__

//-------------------------------------------------------------------------------- class Torus

class Torus: public GeometricObject
{
	public:

		Torus(void);   									// Default constructor

		Torus(const Torus& torus); 						// Copy constructor

		virtual Torus*									// Virtual copy constructor
			clone(void) const;

		virtual												// Destructor
		~Torus(void);   	

}
 
#endif