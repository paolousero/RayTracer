#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "GeometricObject.h"
#include "Vector3D.h"
#include "Normal.h"

//Triangle class============================

class Triangle: public GeometricObject
{
public:
	Triangle(void);						//constructor

	Triangle(const Triangle& triangle);	//copy constructor

	Triangle(const Vector3D v0, const Vector3D v1, const Vector3D v2); //parametized constructor

	virtual Triangle*					//virtual copy constructor
	clone(void) const;

	virtual
	~Triangle(void);					//destructor

	bool
	hit(const Ray& ray, double& tmin, ShadeRec& sr) const ;  //triangle hit function

	virtual bool
	shadow_hit(const Ray& ray, float& tmin)const;

private:
	Vector3D v0;
	Vector3D v1;
	Vector3D v2;
	 static const double kEpsilon;   // for shadows and secondary rays
	Normal normal;
};
#endif