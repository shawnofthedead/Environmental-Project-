#define _USE_MATH_DEFINES
#include <cmath>
#include "Cylinder.h"

#include "GLee.h"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else	
	#include <GL/glut.h>
#endif

#include "Window.h"
#include "vector4.h"
#include "Globals.h"
#include "Texture.h"
#include "math.h"





Cylinder::Cylinder(float startpoint, float radius, float n, float h)
{
	this->h = h;
	this->n = n;
	this->radius = radius;
	this->startpt = startpoint;

}


Cylinder::~Cylinder()
{
}

void Cylinder::render()
{
	float slice = 360 / n;
	float angle = 0.0;
	float new_angle = 0.0;



	glRotated(90.0, 0.0, 1.0, 0.0);

	for (int i = 0; i < n; i++){
		glColor3f(1, 1, 1);
		
		angle = angle + slice;
		new_angle = angle + slice;
		
		float x = (startpt + radius)*cos(angle * (M_PI / 180));
		float new_x = (startpt + radius)*cos(new_angle * (M_PI / 180));
	
		float z = (startpt + radius)*sin(angle * (M_PI / 180));
		float new_z = (startpt + radius)*sin(new_angle * (M_PI / 180));

		head.bind();
		glBegin(GL_QUADS);
		glTexCoord2f(angle / 360, 0);
		glVertex3f(x, startpt + h, z);
		glTexCoord2f(new_angle / 360, 0);
		glVertex3f(new_x, startpt + h, new_z);
		glTexCoord2f(new_angle / 360, 1);
		glVertex3f(new_x, startpt, new_z);
		glTexCoord2f(angle / 360, 1);
		glVertex3f(x, startpt, z);
		
		glEnd();
		head.unbind();

		glBegin(GL_TRIANGLES);
		glVertex3f(startpt, startpt, startpt);
		glVertex3f(x, startpt, z);
		glVertex3f(new_x, startpt, new_z);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(startpt, startpt+h, startpt);
		glVertex3f(x, startpt+h, z);
		glVertex3f(new_x, startpt+h, new_z);
		glEnd();

	}

}

void Cylinder::update(UpdateData& data)
{
	//
	//Matrix4 r;
	//r.makeRotateY(M_PI / 90);
	//toWorld = toWorld* r;

}

void Cylinder::loadTexture()
{
	head = Texture("RobotHead.ppm");
}