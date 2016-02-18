#ifndef CSE167_RenderData_h
#define CSE167_RenderData_h

#include <iostream>
#include "Matrix4.h"

class DrawData
{
    
protected:
	Matrix4 d;
public:
    
    //Payload
    //Place any objects here that you want to pass to a draw() call
	
    
    DrawData(void);
    ~DrawData(void);

	Matrix4 multiply(Matrix4);

	Matrix4 getMatrix();
	void setMatrix(Matrix4);
    
};

#endif
