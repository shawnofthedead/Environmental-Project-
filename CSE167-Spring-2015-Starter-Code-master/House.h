#ifndef CSE167_house_h
#define CSE167_house_h

#include "Drawable.h"

class House : public Drawable 
{

public:
	House();
	virtual ~House(void);

	virtual void draw(DrawData&);
	virtual void myDraw(DrawData&);		//For pa3
	virtual void myDrawPt(DrawData&);
	virtual void update(UpdateData&);
};

#endif

