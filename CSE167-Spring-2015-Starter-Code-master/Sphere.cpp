#include "Sphere.h"
#include "Vector3.h"


#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Sphere::Sphere(double radius, int slices, int stacks) 
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
}

void Sphere::render()
{
  
    glutSolidSphere(radius, slices, stacks);
    
  
}


void Sphere::update(UpdateData& data)
{
    //
}


