#ifndef CSE167_ROBOT_h
#define CSE167_ROBOT_h

#include "Group.h"
#include "MatrixTransform.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Cube.h"
#include "Cylinder.h"

class Robot
{
public:
	Robot();
	~Robot();

	Group* theRoot;

	float angle1, angle2;

	int check;


	MatrixTransform* moveTorso;
	MatrixTransform* scaleTorso;

	MatrixTransform* moveHead;

	MatrixTransform* moveLarm;
	MatrixTransform* scaleLarm;
	MatrixTransform* moveLarm2;
	MatrixTransform* rotateLarm;

	MatrixTransform* moveRarm;
	MatrixTransform* scaleRarm;
	MatrixTransform* moveRarm2;
	MatrixTransform* rotateRarm;

	MatrixTransform* moveRleg;
	MatrixTransform* scaleRleg;
	MatrixTransform* moveRleg2;
	MatrixTransform* rotateRleg;

	
	MatrixTransform* moveLleg;
	MatrixTransform* scaleLleg;
	MatrixTransform* moveLleg2;
	MatrixTransform* rotateLleg;

	
	

	Cube* torsoCube;

	Cube* lhandCube;
	Cube* rhandCube;
	Cube* llegCube;
	Cube* rlegCube;
	Cylinder* headCylinder;



	virtual void update(UpdateData&);

	Group* getRoot();



	void loadTexture();

	void move();


};


#endif
