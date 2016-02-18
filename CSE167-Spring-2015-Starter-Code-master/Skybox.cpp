#define _USE_MATH_DEFINES
#include <cmath>
#include "Skybox.h"

#include "GLee.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "vector3.h"
#include "Globals.h"
#include "math.h"
#include "Texture.h"
#include "Geode.h"



Skybox::Skybox(float size)
{
	this->size = size;

}


Skybox::~Skybox()
{
}

void Skybox::render()
{
	float halfSize = size / 2.0;

	
	//Make Skybox
	
	// Draw front face:

	front.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0, 0);
	glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(1, 0);
	glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(1, 1);
	glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(0, 1);
	glVertex3f(-halfSize, -halfSize, halfSize);

	glEnd();

	// Draw left side:
	left.bind();

	glBegin(GL_QUADS);

	glColor3f(1, 1, 1);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(0, 0);
	glVertex3f(-halfSize, halfSize, -halfSize);
	glTexCoord2f(0, 1);
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 1);
	glVertex3f(-halfSize, -halfSize, halfSize);

	glEnd();

	// Draw right side:
	right.bind();

	glBegin(GL_QUADS);

	glColor3f(1, 1, 1);
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(1, 0);
	glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(1, 1);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(0, 1);
	glVertex3f(halfSize, -halfSize, halfSize);

	glEnd();


	// Draw back face:
	back.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1, 0);
	glVertex3f(-halfSize, halfSize, -halfSize);
	glTexCoord2f(0, 0);
	glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(0, 1);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 1);
	glVertex3f(-halfSize, -halfSize, -halfSize);

	glEnd();

	// Draw top side:

	top.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(1, 1);
	glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(1, 0);
	glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(0, 0);
	glVertex3f(-halfSize, halfSize, -halfSize);

	glEnd();

	// Draw bottom side:

	base.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 1);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 0);
	glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(0, 0);
	glVertex3f(-halfSize, -halfSize, halfSize);

	glEnd();

	//The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
	//glutSolidCube(size);

	//Pop the save state off the matrix stack
	//This will undo the multiply we did earlier
}

void Skybox::update(UpdateData& data)
{
	//

	
}

void Skybox::loadTexture()
{
	left = Texture("PalldioPalace_extern_left.ppm");
	right = Texture("PalldioPalace_extern_right.ppm");
	back = Texture("PalldioPalace_extern_back.ppm");
	top = Texture("PalldioPalace_extern_top.ppm");
	base = Texture("PalldioPalace_extern_base.ppm");
	front = Texture("PalldioPalace_extern_front.ppm");
}

