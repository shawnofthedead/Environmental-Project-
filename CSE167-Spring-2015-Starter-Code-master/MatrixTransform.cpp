#include "MatrixTransform.h"
#include "Matrix4.h"
#include "DrawData.h"



MatrixTransform::MatrixTransform(Matrix4 M)
{
	Transform = M;
}


MatrixTransform::~MatrixTransform()
{
	//
}

void MatrixTransform::draw(DrawData& c){
	DrawData r;
	Matrix4 m;
	m = c.getMatrix()*Transform;
	r.setMatrix(m);
	
	Group::draw(r);
}

void MatrixTransform::update(UpdateData& data){
	//
}

void MatrixTransform::setMatrix(Matrix4 c){
	Transform = c;

}
