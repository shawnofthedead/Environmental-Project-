#include "Geode.h"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

Geode::Geode()
{
}


Geode::~Geode()
{
}

void Geode::draw(DrawData& c){
	

	glMatrixMode(GL_MODELVIEW);

	glLoadMatrixf(c.getMatrix().ptr());
	
	render();


}

