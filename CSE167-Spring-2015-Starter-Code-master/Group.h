#ifndef CSE167_Group_h
#define CSE167_Group_h

#include "Node.h"
#include <list>

using namespace std;

class Group : public Node
{
public:

	list<Node*> childNodes;

	Group();
	~Group();

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);

	void addChild(Node*);
	void removeChild(Node*);
};

#endif

