#include "Triangle.h"
#include "math.h"

const double Triangle::kEpsilon = 0.001;
//constructor
Triangle::Triangle(void)
	: GeometricObject(),
	  v0(0,0,0),
	  v1(0,1,0),
	  v2(1,0,0),
	  normal(0,1,0)
{}

//parametized constructor
Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c)
	:v0(a),
	 v1(b),
	 v2(c)
{
		 normal = (v1-v0)^(v2-v0);
		 normal.normalize();
}

//clone 
Triangle* 
Triangle::clone(void) const
{
	return new Triangle(*this);
}

bool
Triangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {

                double a = v0.x - v1.x, b= v0.x - v2.x, c= ray.d.x, d= v0.x- ray.o.x;
                double e = v0.y - v1.y, f= v0.y - v2.y, g= ray.d.y, h= v0.y- ray.o.y;
                double i = v0.z - v1.z, j= v0.z - v2.z, k= ray.d.z, l= v0.z- ray.o.z;

                double m = f*k - g*j, n= h*k- g*l, p= f*l - h*j;
                double q= g*i - e*k, s= e*j- f*i;
                double inv_denom = 1.0/ (a*m+ b*q + c*s);
                double e1 = d*m - b*n - c*p;
                double beta = e1*inv_denom;
                if (beta <0.0)
                {
                        return (false);
                }
                double r= r= e*l - h*i;
                double e2 = a*n + d*q + c*r;
                double gamma = e2*inv_denom;

                if (gamma <0.0)
                {
                        return (false);
                }

                if (beta + gamma > 1.0)
                {
                        return (false);
                }
                double e3 = a*p - b*r + d*s;
                double t = e3*inv_denom;
                if (t< kEpsilon)
                {
                        return (false);
                }
                tmin = t;
                sr.normal = normal;
                sr.local_hit_point = ray.o + t*ray.d;
                return (true);

}

//copy constructor
Triangle::Triangle(const Triangle& triangle)
	: GeometricObject(triangle),
	  v0(triangle.v0),
	  v1(triangle.v1),
	  v2(triangle.v2),
	  normal(triangle.normal)
{}

//destructor
Triangle::~Triangle(void){}

//----------------------------------------------------------------shadow_hit

bool
Triangle::shadow_hit(const Ray& ray, float& tmin)const
{
	
                double a = v0.x - v1.x, b= v0.x - v2.x, c= ray.d.x, d= v0.x- ray.o.x;
                double e = v0.y - v1.y, f= v0.y - v2.y, g= ray.d.y, h= v0.y- ray.o.y;
                double i = v0.z - v1.z, j= v0.z - v2.z, k= ray.d.z, l= v0.z- ray.o.z;

                double m = f*k - g*j, n= h*k- g*l, p= f*l - h*j;
                double q= g*i - e*k, s= e*j- f*i;
                double inv_denom = 1.0/ (a*m+ b*q + c*s);
                double e1 = d*m - b*n - c*p;
                double beta = e1*inv_denom;
                if (beta <0.0)
                {
                        return (false);
                }
                double r= r= e*l - h*i;
                double e2 = a*n + d*q + c*r;
                double gamma = e2*inv_denom;

                if (gamma <0.0)
                {
                        return (false);
                }

                if (beta + gamma > 1.0)
                {
                        return (false);
                }
                double e3 = a*p - b*r + d*s;
                double t = e3*inv_denom;
                if (t< kEpsilon)
                {
                        return (false);
                }
                tmin = t;
               // sr.normal = normal;
                //sr.local_hit_point = ray.o + t*ray.d;
                return (true);
}