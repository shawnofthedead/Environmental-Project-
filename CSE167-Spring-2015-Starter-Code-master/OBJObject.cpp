#include "OBJObject.h"
#include "GLee.h"
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include "Window.h"
#include "Globals.h"
#include "math.h"
#include <sstream>
#include <fstream>

#define deleteVector(__vect__) do {\
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
								   while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
							   } while(false)


OBJObject::OBJObject(std::string filename) : Drawable()
{
	this->vertices = new std::vector<Vector3*>();
	this->normals = new std::vector<Vector3*>();
	this->texcoords = new std::vector<Vector3*>();
	this->faces = new std::list<Face>();

	parse(filename);
}

OBJObject::~OBJObject()
{
	//Delete any dynamically allocated memory/objects here
	std::vector<Vector3*>::iterator iter;
	std::vector<Vector3*>::iterator end;

	deleteVector(vertices);
	deleteVector(normals);
	deleteVector(texcoords);

	delete faces;
}

void OBJObject::draw(DrawData& data)
{
	material.apply();

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	glBegin(GL_TRIANGLES);
	
	glColor3f(0.6, 0.6, 0.6);
	for (std::list<Face>::iterator it = this->faces->begin(), end = this->faces->end(); it != end; ++it){

		Vector3* v1;
		Vector3* v2;
		Vector3* v3;
		Vector3* n1;
		Vector3* n2;
		Vector3* n3;

		float vx1, vy1, vz1;
		float vx2, vy2, vz2;
		float vx3, vy3, vz3;

		float nx1, ny1, nz1;
		float nx2, ny2, nz2;
		float nx3, ny3, nz3;


		v1 = vertices->at((*it).vs[0]);
		v2 = vertices->at((*it).vs[1]);
		v3 = vertices->at((*it).vs[2]);

		n1 = normals->at((*it).ns[0]);
		n2 = normals->at((*it).ns[1]);
		n3 = normals->at((*it).ns[2]);

		vx1 = (*v1)[0];
		vy1 = (*v1)[1];
		vz1 = (*v1)[2];

		vx2 = (*v2)[0];
		vy2 = (*v2)[1];
		vz2 = (*v2)[2];

		vx3 = (*v3)[0];
		vy3 = (*v3)[1];
		vz3 = (*v3)[2];

		nx1 = (*n1)[0];
		ny1 = (*n1)[1];
		nz1 = (*n1)[2];

		nx2 = (*n2)[0];
		ny2 = (*n2)[1];
		nz2 = (*n2)[2];

		nx3 = (*n3)[0];
		ny3 = (*n3)[1];
		nz3 = (*n3)[2];



		//glTex(tx, ty, tz);
		glNormal3f(nx1, ny1, nz1);
		glVertex3f(vx1, vy1, vz1);

		glNormal3f(nx2, ny2, nz2);
		glVertex3f(vx2, vy2, vz2);

		glNormal3f(nx3, ny3, nz3);
		glVertex3f(vx3, vy3, vz3);
	}


	glEnd();

	glPopMatrix();
}

void OBJObject::myDraw(DrawData& data)
{
	material.apply();

	//glColor3f(0.6, 0.6, 0.6);
	for (std::list<Face>::iterator it = this->faces->begin(), end = this->faces->end(); it != end; ++it){

		Vector3* v1;
		Vector3* v2;
		Vector3* v3;
		Vector3* n1;
		Vector3* n2;
		Vector3* n3;

		float vx1, vy1, vz1;
		float vx2, vy2, vz2;
		float vx3, vy3, vz3;

		float nx1, ny1, nz1;
		float nx2, ny2, nz2;
		float nx3, ny3, nz3;


		v1 = vertices->at((*it).vs[0]);
		v2 = vertices->at((*it).vs[1]);
		v3 = vertices->at((*it).vs[2]);

		n1 = normals->at((*it).ns[0]);
		n2 = normals->at((*it).ns[1]);
		n3 = normals->at((*it).ns[2]);

		vx1 = (*v1)[0];
		vy1 = (*v1)[1];
		vz1 = (*v1)[2];

		vx2 = (*v2)[0];
		vy2 = (*v2)[1];
		vz2 = (*v2)[2];

		vx3 = (*v3)[0];
		vy3 = (*v3)[1];
		vz3 = (*v3)[2];

		nx1 = (*n1)[0];
		ny1 = (*n1)[1];
		nz1 = (*n1)[2];

		nx2 = (*n2)[0];
		ny2 = (*n2)[1];
		nz2 = (*n2)[2];

		nx3 = (*n3)[0];
		ny3 = (*n3)[1];
		nz3 = (*n3)[2];

	
		//glNormal3f(nx1, ny1, nz1);
		Vector3 nv1;
		nv1.set(nx1, ny1, nz1);
		nv1 = toWorld * nv1;
		nv1 = nv1.normalize();

		//glVertex3f(vx1, vy1, vz1);
		Vector4 vv1;
		vv1.set(vx1, vy1, vz1, 1);
		vv1 = toWorld * vv1;

		//glNormal3f(nx2, ny2, nz2);
		Vector3 nv2;
		nv2.set(nx2, ny2, nz2);
		nv2 = toWorld * nv2;
		nv2 = nv2.normalize();

		//glVertex3f(vx2, vy2, vz2);
		Vector4 vv2;
		vv2.set(vx2, vy2, vz2, 1);
		vv2 = toWorld * vv2;

		//glNormal3f(nx3, ny3, nz3);
		Vector3 nv3;
		nv3.set(nx3, ny3, nz3);
		nv3 = toWorld * nv3;
		nv3 = nv3.normalize();

		//glVertex3f(vx3, vy3, vz3);
		Vector4 vv3;
		vv3.set(vx3, vy3, vz3, 1);
		vv3 = toWorld * vv3;

		Globals::rasterizer.drawTriangle(nv1, nv2, nv3, vv1, vv2, vv3);
	}

}

void OBJObject::myDrawPt(DrawData& data)
{
	material.apply();

	//glColor3f(0.6, 0.6, 0.6);
	for (std::list<Face>::iterator it = this->faces->begin(), end = this->faces->end(); it != end; ++it){

		Vector3* v1;
		Vector3* v2;
		Vector3* v3;

		float vx1, vy1, vz1;
		float vx2, vy2, vz2;
		float vx3, vy3, vz3;


		v1 = vertices->at((*it).vs[0]);
		v2 = vertices->at((*it).vs[1]);
		v3 = vertices->at((*it).vs[2]);


		vx1 = (*v1)[0];
		vy1 = (*v1)[1];
		vz1 = (*v1)[2];

		vx2 = (*v2)[0];
		vy2 = (*v2)[1];
		vz2 = (*v2)[2];

		vx3 = (*v3)[0];
		vy3 = (*v3)[1];
		vz3 = (*v3)[2];

		//glVertex3f(vx1, vy1, vz1);
		Vector4 vv1;
		vv1.set(vx1, vy1, vz1, 1);
		vv1 = toWorld * vv1;

		//glVertex3f(vx2, vy2, vz2);
		Vector4 vv2;
		vv2.set(vx2, vy2, vz2, 1);
		vv2 = toWorld * vv2;


		//glVertex3f(vx3, vy3, vz3);
		Vector4 vv3;
		vv3.set(vx3, vy3, vz3, 1);
		vv3 = toWorld * vv3;

		Globals::rasterizer.drawPoint(vv1);
		Globals::rasterizer.drawPoint(vv2);
		Globals::rasterizer.drawPoint(vv3);
	}

}

void OBJObject::update(UpdateData& data)
{
	//
}

void OBJObject::parse(std::string& filename)
{
	std::ifstream infile(filename);
	std::string line;
	std::vector<std::string> tokens;
	std::string token;
	
	std::vector<std::string> faceMelter;
	std::vector<std::string> faceMelter2;
	std::vector<std::string> faceMelter3;

	int lineNum = 0;

	vertices->push_back(new Vector3(0, 0, 0));
	normals->push_back(new Vector3(0, 0, 0));


	std::cout << "Starting parse..." << std::endl;

	//While all your lines are belong to us
	while (std::getline(infile, line))
	{
		//Progress
		if (++lineNum % 10000 == 0)
			std::cout << "At line " << lineNum << std::endl;

		//Split a line into tokens by delimiting it on spaces
		//"Er Mah Gerd" becomes ["Er", "Mah", "Gerd"]
		tokens.clear();
		tokens = split(line, ' ', tokens);

		//If first token is a v then it gots to be a vertex
		
		if (tokens.size() > 0 && tokens.at(0).compare("v") == 0)
		{	
			
			//Parse the vertex line
			float x = std::stof(tokens.at(1));
			float y = std::stof(tokens.at(2));
			float z = std::stof(tokens.at(3));
			vertices->push_back(new Vector3(x, y, z));
		}
		else if (tokens.size() > 0 && tokens.at(0).compare("vn") == 0)
		{
			//Parse the normal line
			float x = std::stof(tokens.at(1));
			float y = std::stof(tokens.at(2));
			float z = std::stof(tokens.at(3));
			Vector3* normal = new Vector3(x, y, z);
			Vector3 normal2 = normal->normalize();
			normals->push_back(new Vector3(normal2[0], normal2[1], normal2[2]));
		}
		else if (tokens.size() > 0 && tokens.at(0).compare("f") == 0)
		{
			Face obj_face;

				
			faceMelter = split(tokens.at(1), '/', faceMelter);

			faceMelter2 = split(tokens.at(2), '/', faceMelter2);
				
			faceMelter3 = split(tokens.at(3), '/', faceMelter3);

			obj_face.vs[0] = std::stof(faceMelter.at(0));
			obj_face.vs[1] = std::stof(faceMelter2.at(0));
			obj_face.vs[2] = std::stof(faceMelter3.at(0));

			obj_face.ns[0] = std::stof(faceMelter.at(2));
			obj_face.ns[1] = std::stof(faceMelter2.at(2));
			obj_face.ns[2] = std::stof(faceMelter3.at(2));
				

		
	
			//Parse the face line
			faceMelter.clear();
			faceMelter2.clear();
			faceMelter3.clear();
			this->faces->push_back(obj_face);
		}
		else if (tokens.size() > 0 && tokens.at(0).compare("how does I are c++?!?!!"))
		{
			//Parse as appropriate
			//There are more line types than just the above listed
			//See the Wavefront Object format specification for details
		}

	}

	std::cout << "Done parsing." << std::endl;
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}