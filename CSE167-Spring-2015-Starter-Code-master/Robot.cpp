#include "Robot.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Globals.h"


#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

Robot::Robot()
{
	theRoot = new Group();

	angle1 = 2.4;
	angle2 = 3.0;

	check = 1;


	// Draw torso, head, left-hand, right-hand, left-leg, right-leg
	torsoCube = new Cube(4.0);
	headCylinder = new Cylinder(0, 2, 10000, 3);
	lhandCube = new Cube(2.0);
	rhandCube = new Cube(2.0);
	llegCube = new Cube(3.0);
	rlegCube = new Cube(3.0);


	//move torso (which includes the whole robot)
	Matrix4 torsoT;
	torsoT.makeTranslate(Vector3(-15, -65.0, 10));
	moveTorso = new MatrixTransform(torsoT);

	theRoot->addChild(moveTorso);

	//scale torso (the whole robot)
	Matrix4 torsoS;
	torsoS.makeScale(0.3,0.3,0.2);

	scaleTorso = new MatrixTransform(torsoS);
	moveTorso->addChild(scaleTorso);

	//add Torso Cube
	scaleTorso->addChild(torsoCube);

	//move head
	Matrix4 headT;
	Vector3 headTv = Vector3(0, 2.5, 0);
	headT.makeTranslate(headTv);
	moveHead = new MatrixTransform(headT);
	scaleTorso->addChild(moveHead);

	// add Head Cylinder
	moveHead->addChild(headCylinder);

	//move left arm 2
	Matrix4 larmM;
	Vector3 larmMv = Vector3(0, 1, 0);
	larmM.makeTranslate(larmMv);
	moveLarm2 = new MatrixTransform(larmM);
	scaleTorso->addChild(moveLarm2);
	

	//rotate left arm
	Matrix4 larmR;
	larmR.makeRotateX(angle1);
	rotateLarm = new MatrixTransform(larmR);
	moveLarm2->addChild(rotateLarm);

	//move left arm
	Matrix4 larmT;
	Vector3 larmTv = Vector3(-2.5, 1.5, 0);
	larmT.makeTranslate(larmTv);
	moveLarm = new MatrixTransform(larmT);
	rotateLarm->addChild(moveLarm);

	//scale left arm
	Matrix4 larmS;
	larmS.makeScale(0.7, 2.5, 0.7);
	scaleLarm = new MatrixTransform(larmS);
	moveLarm->addChild(scaleLarm);
	

	//add Left arm Cube
	scaleLarm->addChild(lhandCube);


	//move right arm 2
	Matrix4 rarmM;
	Vector3 rarmMv = Vector3(0, 1, 0);
	rarmM.makeTranslate(rarmMv);
	moveRarm2 = new MatrixTransform(rarmM);
	scaleTorso->addChild(moveRarm2);


	//rotate right arm
	Matrix4 rarmR;
	rarmR.makeRotateX(angle2);
	rotateRarm = new MatrixTransform(rarmR);
	moveRarm2->addChild(rotateRarm);

	//move right arm
	Matrix4 rarmT;
	Vector3 rarmTv = Vector3(2.5, 1.5, 0);
	rarmT.makeTranslate(rarmTv);
	moveRarm = new MatrixTransform(rarmT);
	rotateRarm->addChild(moveRarm);

	//scale right arm
	Matrix4 rarmS;
	rarmS.makeScale(0.7, 2.5, 0.7);
	scaleRarm = new MatrixTransform(rarmS);
	moveRarm->addChild(scaleRarm);

	//add Right arm Cube
	scaleRarm->addChild(rhandCube);

	//move right leg 2
	Matrix4 rlegM;
	Vector3 rlegMv = Vector3(0, -1.0, 0);
	rlegM.makeTranslate(rlegMv);
	moveRleg2 = new MatrixTransform(rlegM);
	scaleTorso->addChild(moveRleg2);

	//rotate right leg
	Matrix4 rlegR;
	rlegR.makeRotateX(-3.1415926 + angle1);
	rotateRleg = new MatrixTransform(rlegR);
	moveRleg2->addChild(rotateRleg);

	//move right leg
	Matrix4 rlegT;
	Vector3 rlegTv = Vector3(1.0, -3.0, 0);
	rlegT.makeTranslate(rlegTv);
	moveRleg = new MatrixTransform(rlegT);
	rotateRleg->addChild(moveRleg);

	

	//scale right leg
	Matrix4 rlegS;
	rlegS.makeScale(0.5, 2.5, 0.5);
	scaleRleg = new MatrixTransform(rlegS);
	moveRleg->addChild(scaleRleg);

	//add Right leg Cube
	scaleRleg->addChild(rlegCube);

	//move left leg 2
	Matrix4 llegM;
	Vector3 llegMv = Vector3(0, -1.0, 0);
	llegM.makeTranslate(llegMv);
	moveLleg2 = new MatrixTransform(llegM);
	scaleTorso->addChild(moveLleg2);

	//rotate left leg
	Matrix4 llegR;
	llegR.makeRotateX(-3.1415926 + angle2);
	rotateLleg = new MatrixTransform(llegR);
	moveLleg2->addChild(rotateLleg);

	//move left leg
	Matrix4 llegT;
	Vector3 llegTv = Vector3(-1.0, -2.5, 0);
	llegT.makeTranslate(llegTv);
	moveLleg = new MatrixTransform(llegT);
	rotateLleg->addChild(moveLleg);



	//scale left leg
	Matrix4 llegS;
	llegS.makeScale(0.5, 2.5, 0.5);
	scaleLleg = new MatrixTransform(llegS);
	moveLleg->addChild(scaleLleg);

	//add left leg Cube
	scaleLleg->addChild(llegCube);


}


Robot::~Robot()
{
}
 

void Robot::update(UpdateData& data){
	
	//std::cout << angle << std::endl;
	if (angle1 > 3.0){
		check = -1;
	}
	if (angle1 < 2.4 ){
		check = 1;
	}
	angle1 = angle1 + 0.8*check;
	angle2 = angle2 - 0.8*check;

}

Group* Robot::getRoot(){
	return theRoot;
}



void Robot::loadTexture(){
	headCylinder->loadTexture();}

void Robot::move(){
	Matrix4 r1, r2, r3, r4;
	r1.makeRotateX(angle1);
	r2.makeRotateX(angle2);
	r3.makeRotateX(angle1 - 3.1415926);
	r4.makeRotateX(angle2 - 3.1415926);
	rotateLarm->setMatrix(r1);
	rotateRarm->setMatrix(r2);
	rotateRleg->setMatrix(r3);
	rotateLleg->setMatrix(r4);
}