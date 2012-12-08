#include "BBox.h"
#include "Constants.h"

// default constructor
BBox::BBox(void)
	: x0(-1), y0(-1), z0(-1),
	  x1(1), y1(1), z1(1)
{}

// copy constructor
BBox::BBox(const BBox& bbox)
	:x0(bbox.x0), y0(bbox.y0), z0(bbox.z0),
	 x1(bbox.x1), y1(bbox.y1), z1(bbox.z1)
{}

//double constructor
BBox::BBox(const double x0, const double y0, const double z0,
		   const double x1, const double y1, const double z1)
	:x0(x0), y0(y0), z0(z0),
	x1(x1), y1(y1), z1(z1)
{}

//ray constructor
BBox::BBox(const Point3D p0, const Point3D p1)
	:x0(p0.x), y0(p0.y), z0(p0.z),
	x1(p1.x), y1(p1.y), z1(p1.z)
{}


//hit function
bool
BBox::hit(const Ray& ray)
{
//makes things easier to type later.
	double ox = ray.o.x; double oy = ray.o.y; double oz = ray.o.z;
	double dx = ray.d.x; double dy = ray.d.y; double dz = ray.d.z;

//setting the minimums and maximums.
	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	double a= 1.0/dx;
	double b = 1.0 / dy;
	double c = 1.0 / dz;

	if(a >=0)
	{
		tx_min =(x0 - ox) * a;
		tx_max =(x1 - ox) * a;
	}
	else
	{
		tx_min =(x1 - ox) * a;
		tx_max =(x0 - ox) * a;
	}

	
	if(b >=0)
	{
		ty_min =(y0 - oy) * b;
		ty_max =(y1 - oy) * b;
	}
	else
	{
		ty_min =(y1 - oz) * b;
		ty_max =(y0 - oz) * b;
	}

	
	if(c >=0)
	{
		tz_min =(z0 - oz) * c;
		tz_max =(z1 - oz) * c;
	}
	else
	{
		tz_min =(z1 - oz) * c;
		tz_max =(z0 - oz) * c;
	}

	double t0, t1;

	//finding the face.
	if(tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;
	if(tz_min > t0)
		t0 = tz_min;

	//finding max
	if(tx_max > ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;
	if(tz_max > t1)
		t1 = tz_max;

	return (t0 <t1 && t1 > kEpsilon);
}