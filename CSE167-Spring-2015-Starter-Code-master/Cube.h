#ifndef CSE167_Cube_h
#define CSE167_Cube_h

#include "Geode.h"

class Cube : public Geode
{
    
public:
    
    float size;
    
    Cube(float);
    virtual ~Cube(void);
    
    virtual void render();

    virtual void update(UpdateData&);
    

	
	
    
};

#endif

