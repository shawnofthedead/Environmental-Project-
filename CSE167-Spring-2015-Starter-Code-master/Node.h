#ifndef CSE167_Node_h
#define CSE167_Node_h

#include <iostream>
#include "Matrix4.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Material.h"
#include <float.h>
#include <math.h>
#include <vector>
#include <list>

class Node
{
public:
	Node();
	~Node();

	
	virtual void draw(DrawData&) = 0;
	virtual void update(UpdateData&) = 0;
};

#endif

