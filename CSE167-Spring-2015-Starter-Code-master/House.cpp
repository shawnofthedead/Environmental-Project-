#include "House.h"
#include "Rasterizer.h"
#include "Globals.h"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include "Window.h"
#include "Vector3.h"

// This data structure defines a simple house

int nVerts = 42;    // your vertex array needs to have this many entries

// These are the x,y,z coordinates of the vertices of the triangles
float vertices[] = {
	-4, -4, 4, 4, -4, 4, 4, 4, 4, -4, 4, 4,     // front face
	-4, -4, -4, -4, -4, 4, -4, 4, 4, -4, 4, -4, // left face
	4, -4, -4, -4, -4, -4, -4, 4, -4, 4, 4, -4,  // back face
	4, -4, 4, 4, -4, -4, 4, 4, -4, 4, 4, 4,     // right face
	4, 4, 4, 4, 4, -4, -4, 4, -4, -4, 4, 4,     // top face
	-4, -4, 4, -4, -4, -4, 4, -4, -4, 4, -4, 4, // bottom face

	-20, -4, 20, 20, -4, 20, 20, -4, -20, -20, -4, -20, // grass
	-4, 4, 4, 4, 4, 4, 0, 8, 4,                       // front attic wall
	4, 4, 4, 4, 4, -4, 0, 8, -4, 0, 8, 4,               // left slope
	-4, 4, 4, 0, 8, 4, 0, 8, -4, -4, 4, -4,             // right slope
	4, 4, -4, -4, 4, -4, 0, 8, -4 };                   // rear attic wall

// These are the RGB colors corresponding to the vertices, in the same order
float colors[] = {
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // front is red
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // left is green
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // back is red
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // right is green
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // top is blue
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // bottom is blue

	0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, // grass is dark green
	0, 0, 1, 0, 0, 1, 0, 0, 1,                // front attic wall is blue
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,         // left slope is green
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,         // right slope is red
	0, 0, 1, 0, 0, 1, 0, 0, 1, };              // rear attic wall is red

// The index data stores the connectivity of the triangles; 
// index 0 refers to the first triangle defined above
int indices[] = {
	0, 2, 3, 0, 1, 2,      // front face
	4, 6, 7, 4, 5, 6,      // left face
	8, 10, 11, 8, 9, 10,     // back face
	12, 14, 15, 12, 13, 14,   // right face
	16, 18, 19, 16, 17, 18,   // top face
	20, 22, 23, 20, 21, 22,   // bottom face

	24, 26, 27, 24, 25, 26,   // grass
	28, 29, 30,             // front attic wall
	31, 33, 34, 31, 32, 33,   // left slope
	35, 37, 38, 35, 36, 37,   // right slope
	39, 40, 41 };            // rear attic wall

House::House() : Drawable()
{
	
}


House::~House()
{
	//Delete any dynamically allocated memory/objects here
}

void House::draw(DrawData& data)
{

	material.apply();

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	glBegin(GL_TRIANGLES);

	int index = -1;
	float red = 0.0;
	float green = 0.0;
	float blue = 0.0;
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

	for (int i = 0; i < 60; i++)
	{
		index = indices[i];
		red = colors[index*3];
		green = colors[index * 3 + 1];
		blue = colors[index * 3 + 2];

		x = vertices[index * 3];
		y = vertices[index * 3 + 1];
		z = vertices[index * 3 + 2];

		
		glColor3f(red, green, blue);
		
		
		Vector3 v = Vector3(x, y, z);
		

		glVertex3f(x, y, z);


	}
	glEnd();

	glPopMatrix();

}

void House::myDraw(DrawData& data)
{

	material.apply();

	int index = -1;
	int index2 = -1;
	int index3 = -1;

	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
	float x2 = 0.0;
	float y2 = 0.0;
	float z2 = 0.0;
	float x3 = 0.0;
	float y3 = 0.0;
	float z3 = 0.0;

	float red1 = 0.0;
	float green1 = 0.0;
	float blue1 = 0.0;
	float red2 = 0.0;
	float green2 = 0.0;
	float blue2 = 0.0;
	float red3 = 0.0;
	float green3 = 0.0;
	float blue3 = 0.0;

	for (int i = 0; i < 60; i+=3)
	{
		index = indices[i];
		index2 = indices[i + 1];
		index3 = indices[i + 2];

		red1 = colors[index * 3];
		green1 = colors[index * 3 + 1];
		blue1 = colors[index * 3 + 2];

		red2 = colors[index2 * 3];
		green2 = colors[index2 * 3 + 1];
		blue2 = colors[index2 * 3 + 2];

		red3 = colors[index3 * 3];
		green3 = colors[index3 * 3 + 1];
		blue3 = colors[index3 * 3 + 2];


		x = vertices[index * 3];
		y = vertices[index * 3 + 1];
		z = vertices[index * 3 + 2];

		x2 = vertices[index2 * 3];
		y2 = vertices[index2 * 3 + 1];
		z2 = vertices[index2 * 3 + 2];

		x3 = vertices[index3 * 3];
		y3 = vertices[index3 * 3 + 1];
		z3 = vertices[index3 * 3 + 2];


		Vector4 p, p2, p3;
		p.set(x, y, z, 1);
		p = toWorld * p;
		p2.set(x2, y2, z2, 1);
		p2 = toWorld * p2;
		p3.set(x3, y3, z3, 1);
		p3 = toWorld * p3;


		Vector3 norm;
		norm.set(red1, green1, blue1);
		norm = toWorld * norm;
		norm = norm.normalize();

		Vector3 norm2;
		norm2.set(red2, green2, blue2);
		norm2 = toWorld * norm2;
		norm2 = norm2.normalize();

		Vector3 norm3;
		norm3.set(red3, green3, blue3);
		norm3 = toWorld * norm3;
		norm3 = norm3.normalize();

		Globals::rasterizer.drawTriangle(norm, norm2, norm3, p, p2, p3);
	
	}
}

void House::myDrawPt(DrawData& data)
{

	material.apply();

	int index = -1;

	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

	for (int i = 0; i < 60; i++)
	{
		index = indices[i];

		x = vertices[index * 3];
		y = vertices[index * 3 + 1];
		z = vertices[index * 3 + 2];

		Vector4 p;
		p.set(x, y, z, 1);
		p = toWorld * p;


		Globals::rasterizer.drawPoint(p);

	}
}

void House::update(UpdateData& data)
{
	//
}

