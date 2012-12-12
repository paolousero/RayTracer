#ifndef __BBOX__
#define __BBOX__

#include "Ray.h"
#include "Point3D.h"

class BBox{
	public:

		double x0, y0, z0,
			   x1, y1, z1;

		BBox (void);												//default construcor

		BBox (const BBox& bbox);									//copy constructor

		BBox (const double x0, const double y0, const double z0,	//constructor w/ doubles
			  const double x1, const double y1, const double z1);

		BBox (const Point3D p0, const Point3D p1);					//constructor w/ Point3D

		bool
		hit(const Ray& ray) const;

		virtual
		~BBox (void);												//construcor
};

#endif