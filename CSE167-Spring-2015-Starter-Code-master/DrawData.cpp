#include "DrawData.h"
#include "Matrix4.h"


DrawData::DrawData(void)
{
    //
	
}

DrawData::~DrawData(void)
{
    //
}

Matrix4 DrawData::multiply(Matrix4 a)
{

	return d.multiply(a);
}

void DrawData::setMatrix(Matrix4 a){

	d = a;
}

Matrix4 DrawData::getMatrix(){
	return d;
}
