#pragma once

#include "Matrix4.h"
#include "Drawable.h"
#include "Vector4.h"
#include "Camera.h"


class Rasterizer
{


public:
	Rasterizer();
	~Rasterizer();
	
	Matrix4 D;
	Matrix4 P;
	static bool buffer;

	void drawPoint(Vector4);
	void drawTriangle(Vector3, Vector3, Vector3, Vector4, Vector4, Vector4);
	void display();
	void reshape(int,int,float,float);
	void clearBuffer();

	


};

