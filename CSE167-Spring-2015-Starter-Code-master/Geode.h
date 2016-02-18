#ifndef CSE167_Geode_h
#define CSE167_Geode_h

#include "Node.h"
#include "Material.h"

class Geode : public Node
{
public:
	Geode();
	~Geode();

	virtual void draw(DrawData&);
	virtual void update(UpdateData&) = 0;

	virtual void render() = 0;
	Material material;
	
};



#endif

