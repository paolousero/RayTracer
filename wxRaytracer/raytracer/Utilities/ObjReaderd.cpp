#include "ObjReader.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include "Point3D.h"

// ---------------------------------------------------------------------- default constructor
ObjReader::ObjReader(void)
	: verts(),
	  faces()
{}

// ---------------------------------------------------------------------- assignment operator

ObjReader& 
ObjReader::operator= (const ObjReader& rhs) 	
{
	if (this == &rhs)
		return (*this);
	
	verts	= rhs.verts;
	faces 	= rhs.faces;

	return (*this);
}


//--------------------------------------------------------------------------read file
vector<vector<Point3D>>
ObjReader::read(const string& s){
		int vertNum = 0;
		int faceNum = 0;
		int vertInFace;
	ifstream objFile (s);
	string current;

		if(!objFile){
			//cout<<"There is an error.";
		}
		else if(objFile.is_open())
		{
			while(objFile.good()){
				getline(objFile,current);
				//Vertex stuff = = = = = = = = = = = = = = = 
				if(current.substr(0,2)=="v ")
				{
					verts.push_back(Point3D());

					istringstream s(current.substr(2));
					s >> verts[vertNum].x;
					s >> verts[vertNum].y;
					s >> verts[vertNum].z;

				//	cout<<verts[vertNum].x<<endl;
				//	cout<<verts[vertNum].y<<endl;
				//	cout<<verts[vertNum].z<<endl;
				//	cout<<endl;

					vertNum++;
				}
				//Face stuff = = = = = = = = = = = = = = = 
				else if(current.substr(0,2)=="f ")
				{
					faces.push_back(vector<Point3D>());

					string temp;
					istringstream s(current.substr(2));

						//there are still tokens in the current face line, 
						//keep parsing s and extracting verts.
					while(s.good())
					{
						s >> temp;
						//temp = temp.substr(0,1);
						//vertInFace = atoi(temp.c_str())-1;
						char *copy = strdup(temp.c_str());
						vertInFace = atoi(strtok(copy, "/"));
						faces[faceNum].push_back(verts[vertInFace-1]);

						//onst char* t = temp[0];
						//int x = atoi(t);
						//cout<<faces[faceNum].back();
					}
					faceNum++;	
				}
			}
		}

		return faces;
}