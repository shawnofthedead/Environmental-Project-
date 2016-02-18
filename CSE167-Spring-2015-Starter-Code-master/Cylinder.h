#ifndef CSE167_Cylinder_h
#define CSE167_Cylinder_h

#include "Geode.h"
#include "Texture.h"

class Cylinder : public Geode
{

public:

	Texture head;
	float startpt, radius, h, n;
	Cylinder(float, float, float, float);
	virtual ~Cylinder();

	virtual void render();
	virtual void update(UpdateData&);

	void loadTexture();
};

#endif

