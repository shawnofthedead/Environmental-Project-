#ifndef CSE167_MatrixTransform_h
#define CSE167_MatrixTransform_h

#include "Group.h"
#include "Matrix4.h"


class MatrixTransform : public Group
{
public:

	Matrix4 Transform;

	MatrixTransform(Matrix4);
	~MatrixTransform();

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);

	void setMatrix(Matrix4);
};

#endif

