#include "Group.h"


Group::Group()
{
	//
}


Group::~Group()
{
}

void Group::draw(DrawData& c){
	list<Node*>::iterator it;
	for (it = childNodes.begin(); it != childNodes.end(); ++it){
		(*it)->draw(c);
	}
}

void Group::update(UpdateData&){
	//
}

void Group::addChild(Node* child)
{
	childNodes.push_back(child);
}

void Group::removeChild(Node* child)
{
	
	childNodes.remove(child);
}
