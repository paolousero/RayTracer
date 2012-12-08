#ifndef __OBJREADER__
#define __OBJREADER__


#include <vector>
#include "Point3D.h"
using namespace std;

class ObjReader
{
	public:
		vector<Point3D> verts;
		vector<vector<Point3D>> faces;

		ObjReader(void);

		ObjReader& 									
		operator= (const ObjReader& rhs); 

		vector<vector<Point3D>>
		read(const string& s);

};
#endif
