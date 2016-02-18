#ifndef CSE167_Sphere_h
#define CSE167_Sphere_h

#include <iostream>
#include "Geode.h"

class Sphere : public Geode
{
    
public:
    
    double radius;
	double dx,dy;
	
    int slices, stacks;
    
    Sphere(double, int, int);
    
    virtual void render();
    virtual void update(UpdateData&);

    
};

#endif
