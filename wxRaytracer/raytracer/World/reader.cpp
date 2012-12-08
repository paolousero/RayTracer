#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Point3D.h"
using namespace std;


struct vertex{
	double x;
	double y;
	double z;
}


int main()
{

string current;
vertex vertTemp;
vector<struct vertex> verts;

ifstream objFile ("kalem_OBJ.obj");

if(objFile.is_open())
{
	while(objFile.good()){
		getline(objFile,current);
		if(current.substr(0,2)=="v ")
		{
			istringstream s(current.substr(2));
			s >> vertTemp.x;
			s >> vertTemp.y;
			s >> vertTemp.z;
			cout<<vertTemp.x;
			cout<<vertTemp.y;
			cout<<vertTemp.z;

		}
	}
}


for(int i =0;i<20;i++)
	cout<<(float)rand()+0.1<<endl;
system("PAUSE");
return 0;                                                                                                                                                      
}