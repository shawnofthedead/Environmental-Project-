#ifndef CSE167_Drawable_h
#define CSE167_Drawable_h

#include <iostream>
#include "Matrix4.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Material.h"
#include <float.h>
#include <math.h>
#include <vector>


class Drawable
{
    
public:
    
    Matrix4 toWorld;
    Material material;
    
    Drawable(void);
    ~Drawable(void);
    
    virtual void draw(DrawData&);
	virtual void myDraw(DrawData&);
	virtual void myDrawPt(DrawData&);
    virtual void update(UpdateData&);

	void left(float);
	void right(float);
	void up(float);
	void down(float);
	void into(float);
	void out(float);
	void reset();
	void rotateZ(float);
	void reverseZ(float);
	void scale(float, float, float);
	void getPosition();
};

#endif
