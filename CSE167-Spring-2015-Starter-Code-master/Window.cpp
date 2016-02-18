#include <iostream>

#include "Glee.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <cmath>
#include "Window.h"
#include "Cube.h"
#include "House.h"
#include "Matrix4.h"
#include "vector3.h"
#include "Globals.h"
#include "Skybox.h"
#include "Texture.h"
#include "Camera.h"
#include "Robot.h"
#include "Terrain.h"
#include "MatrixTransform.h"


int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
bool Window::flag = true;	//-- set toggle flag to true at first
bool Window::ball = false;   //-- set ball flag to false at first
bool Window::rasterize_switch = true;	
bool Window::pt_tri = true;
int toggle = 1;
int lightup = 1;

MatrixTransform* scaleWorld;
MatrixTransform* rotateWorld;
MatrixTransform* rotateWorldX;
MatrixTransform* rotateWorldY;
MatrixTransform* moveSphere;
MatrixTransform* moveX;
MatrixTransform* moveY;
MatrixTransform* moveZ;


Matrix4 scale_down, scale_up, move_right, move_left, move_up, move_down, move_forward, mbackward, rotate_Z, sphere_Z, rotate_Y, rotate_X;
Matrix4 rWorld, mxWorld, myWorld, mzWorld, sWorld, sphereW;
Vector4 lightvector;

Vector3 lastpoint = Vector3(0.0, 0.0, 0.0);
int movement = 0;
float Window::scale = 0.1;
float Window::lrmove = -50.0;
float Window::udmove = -20.0;
float Window::fbmove = -150.0;
float Window::degree = 0.0;
float Window::degreeX = 0.0;
float Window::degreeY = 0.0;
float Window::sunX = 0.0;
float Window::sunY = 30.0;
float Window::exY = 1.0;
float Window::flood = 0.0;
Vector4 Window::whiteness = Vector4(0.8, 0.8, 0.0, 1.0);


static float* pixels = new float[Window::width * Window::height * 3];

void Window::initialize(void)
{
	

	//Initialize skybox matrix:
	Globals::skybox->loadTexture();
	Globals::terrain->loadShader();
	//Globals::robot->loadTexture();


	Globals::drawData.setMatrix(Globals::camera->getInverseMatrix());

	// move the world and stuff

	//Globals::root.addChild(Globals::skybox);

	mzWorld.makeTranslate(Vector3(0.0, 0.0, fbmove));
	moveZ = new MatrixTransform(mzWorld);

	Globals::root.addChild(moveZ);

	myWorld.makeTranslate(Vector3(0.0, udmove, 0.0));
	moveY = new MatrixTransform(myWorld);

	moveZ->addChild(moveY);

	mxWorld.makeTranslate(Vector3(lrmove, 0.0, 0.0));
	moveX = new MatrixTransform(mxWorld);

	moveY->addChild(moveX);


	float radiansY = degreeY / 180.0 * 3.1415926;

	rotate_Y.makeRotateY(radiansY);
	rotateWorldY = new MatrixTransform(rotate_Y);

	moveX->addChild(rotateWorldY);

	float radians = degree / 180.0 * 3.1415926;

	rWorld.makeRotateZ(radians);
	rotateWorld = new MatrixTransform(rWorld);

	rotateWorldY->addChild(rotateWorld);

	float radiansX = degreeX / 180.0 * 3.1415926;
	rotate_X.makeRotateX(radiansX);
	rotateWorldX = new MatrixTransform(rotate_X);

	rotateWorld->addChild(rotateWorldX);

	sWorld.makeScale(scale);
	scaleWorld = new MatrixTransform(sWorld);

	rotateWorldX->addChild(scaleWorld);


	scaleWorld->addChild(Globals::terrain);

	sphereW.makeTranslate(sunX, sunY, 1020.0);
	moveSphere = new MatrixTransform(sphereW);

	scaleWorld->addChild(moveSphere);

	moveSphere->addChild(Globals::sphere);

	
	lightCalculation();
	

	//Setup the point light

	//Globals::light->position = lightvector;
	Globals::light->ambientColor = Color(0.2, 0.2, 0.2, 1.0);
	Globals::light->diffuseColor = Color(whiteness[0], whiteness[1], whiteness[2], whiteness[3]);
	Globals::light->specularColor = Color(0.0, 0.0, 0.0, 1.0);


	//Setup the cube's material properties
	Color color(0x23ff27ff);
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
	//Globals::robot->update(Globals::updateData);
	//Globals::robot->move();
	praiseTheSun();

	lightCalculation();
	Globals::light->position = lightvector;
	//std::cout << lightvector[0] << std::endl;
	//std::cout << lightvector[1] << std::endl;
	//std::cout << lightvector[2] << std::endl;

	

    //Call the display routine to draw the cube
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
	
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
	float aspect = (float)width / (float)height;
	float FOV = 60.0 / 180.0 * M_PI;

	glViewport(0, 0, w, h);                                          //Set new viewport size
	glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
	glLoadIdentity();                                                //Clear the projection matrix by loading the identity
	gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0); //Set perspective projection viewing frustum


	Globals::rasterizer.reshape(width, height, aspect, FOV);					//aspect and POV

}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{

	Globals::drawData.setMatrix(Globals::camera->getInverseMatrix());
	//Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	
	//glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
	Globals::light->bind(0);

	Globals::root.draw(Globals::drawData);

	
	glPopMatrix();
	//Tell OpenGL to clear any outstanding commands in its command buffer
	//This will make sure that all of our commands are fully executed before
	//we swap buffers and show the user the freshly drawn frame
	glFlush();

	//Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
	glutSwapBuffers();
}


//TODO: Keyboard callbacks!

void Window::keyboardCallback(unsigned char key, int x, int y)
{
	
	switch (key) {
	case 'S':
		scale = scale * 1.1;
		scale_up.makeScale(scale);
		scaleWorld->setMatrix(scale_up);

		break;
	case 's':
		scale = scale * 0.9;
		scale_down.makeScale(scale);
		scaleWorld->setMatrix(scale_down);

		break;
	case 'x':
		lrmove = lrmove + 2.0;
		move_right.makeTranslate(lrmove, 0.0, 0.0);
		moveX->setMatrix(move_right);

		break;
	case 'X':
		lrmove = lrmove - 2.0;
		move_left.makeTranslate(lrmove, 0.0, 0.0);
		moveX->setMatrix(move_left);

		break;
	case 'y':
		udmove = udmove + 2.0;
		move_up.makeTranslate(0.0, udmove, 0.0);
		moveY->setMatrix(move_up);

		break;
	case 'Y':
		udmove = udmove - 2.0;
		move_down.makeTranslate(0.0, udmove, 0.0);
		moveY->setMatrix(move_down);

		break;
	case 'z':
		fbmove = fbmove + 2.0;
		move_forward.makeTranslate(0.0, 0.0, fbmove);
		moveZ->setMatrix(move_forward);

		break;
	case 'Z':
		fbmove = fbmove - 2.0;
		mbackward.makeTranslate(0.0, 0.0, fbmove);
		moveZ->setMatrix(mbackward);

		break;
	case 'o':
		degree = degree + 10.0;
		rotate_Z.makeRotateZ(degree / 180 * M_PI);
		rotateWorld->setMatrix(rotate_Z);

		break;
	case 'O':
		degree = degree - 10.0;
		rotate_Z.makeRotateZ(degree / 180 * M_PI);
		rotateWorld->setMatrix(rotate_Z);

		break;
	case 't':
		flag = !flag;
		break;

	case 'p':
		degreeX = degreeX + 10.0;
		rotate_X.makeRotateX(degreeX / 180 * M_PI);
		rotateWorldX->setMatrix(rotate_X);

		break;
	case 'P':
		degreeX = degreeX - 10.0;
		rotate_X.makeRotateX(degreeX / 180 * M_PI);
		rotateWorldX->setMatrix(rotate_X);

		break;
	case 'q':
		degreeY = degreeY + 10.0;
		rotate_Y.makeRotateY(degreeY / 180 * M_PI);
		rotateWorldY->setMatrix(rotate_Y);

		break;
	case 'Q':
		degreeY = degreeY - 10.0;
		rotate_Y.makeRotateY(degreeY / 180 * M_PI);
		rotateWorldY->setMatrix(rotate_Y);

		break;
	}

}

//TODO: Function Key callbacks!

//TODO: Mouse callbacks!
void Window::mouseCallback(int button, int state, int x, int y)
{

	lastpoint = trackBallMapping(x, y);
	switch (button){
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN){
			movement = GLUT_LEFT_BUTTON;

		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN){
			movement = GLUT_RIGHT_BUTTON;

		}
		break;

	}

}

//TODO: Mouse Motion callbacks!
void Window::motionCallback(int x, int y)
{
	Vector3 direction;
	float rot_angle;
	Vector3 curPoint;
	float velocity;
	Matrix4 move;

	curPoint = trackBallMapping(x, y);
	direction = curPoint - lastpoint;

	Vector3 forward = Globals::camera->d - Globals::camera->e;
	forward = forward.normalize();
	Vector3 backward = forward.negate();

	Vector3 right = forward.cross(Globals::camera->up);
	Vector3 left = right.negate();

	Vector3 up = right.cross(forward);
	up = up.normalize();

	Vector3 down = up.negate();

	Vector3 lookAt = Globals::camera->d - Globals::camera->e;


	switch (movement) {
	case GLUT_LEFT_BUTTON:
		if (x > (width - 100)){
			if (direction[1] > 0.0){
				flood = flood + 10.0;
			}
			if (direction[1] < 0.0){
				flood = flood - 10.0;
			}
		}
		else if (x < 100){
			if (direction[1] > 0.0){
				exY = exY + 0.1;
			}
			if (direction[1] < 0.0){
				exY = exY - 0.1;
			}
		}
		else{
			velocity = direction.magnitude();
			if (velocity > 0.0001){
				Vector3 rotAxis;
				rotAxis = lastpoint.cross(curPoint);

				rot_angle = asin(rotAxis.magnitude() / (lastpoint.magnitude() * curPoint.magnitude()));
				rot_angle = rot_angle * 3.1415926 / 180.0;
				rotAxis = rotAxis.normalize();

				Matrix4 r;
				r = r.makeRotateArbitrary(rotAxis, 16.0 * rot_angle);

				Globals::camera->d = Globals::camera->e + r* lookAt;

				lastpoint = curPoint;
			}
			Globals::camera->update();
		}

		break;
		
	case GLUT_RIGHT_BUTTON:
		
		
			if (direction[0] > 0.0){
				Globals::camera->e = Globals::camera->e + right* 2.0;
				Globals::camera->d = Globals::camera->d + right* 2.0;
			}
			if (direction[0] < 0.0){
				Globals::camera->e = Globals::camera->e + left* 2.0;
				Globals::camera->d = Globals::camera->d + left* 2.0;
			}
			if (direction[1] > 0.0){
				Globals::camera->e = Globals::camera->e + up* 2.0;
				Globals::camera->d = Globals::camera->d + up* 2.0;
			}
			if (direction[1] < 0.0){
				Globals::camera->e = Globals::camera->e + down* 2.0;
				Globals::camera->d = Globals::camera->d + down* 2.0;
			}
			Globals::camera->update();
		
		break;
	
	}


}

Vector3 Window::trackBallMapping(int x, int y)
{
	Vector3 v;    // Vector v is the synthesized 3D position of the mouse location on the trackball
	float d;     // this is the depth of the mouse location: the delta between the plane through the center of the trackball and the z position of the mouse
	v[0] = (2.0*x - width) / width;   // this calculates the mouse X position in trackball coordinates, which range from -1 to +1
	v[1] = (height - 2.0*y) / height;   // this does the equivalent to the above for the mouse Y position
	v[2] = 0.0;   // initially the mouse z position is set to zero, but this will change below
	d = v.magnitude();    // this is the distance from the trackball's origin to the mouse location, without considering depth (=in the plane of the trackball's origin)
	d = (d<1.0) ? d : 1.0;   // this limits d to values of 1.0 or less to avoid square roots of negative values in the following line
	v[2] = sqrtf(1.001 - d*d);  // this calculates the Z coordinate of the mouse position on the trackball, based on Pythagoras: v.z*v.z + d*d = 1*1
	v = v.normalize(); // Still need to normalize, since we only capped d, not v.
	return v;  // return the mouse location on the surface of the trackball
}



void Window::lightCalculation(){
	Matrix4 light;
	light.identity();
	light = moveSphere->Transform * light;
	light = scaleWorld->Transform * light;
	light = rotateWorldX->Transform * light;
	light = rotateWorld->Transform * light;
	light = rotateWorldY->Transform * light;
	light = moveX->Transform * light;
	light = moveY->Transform * light;
	light = moveZ->Transform * light;
	
	
	light = Globals::camera->getInverseMatrix() * light;
	lightvector = Vector4(light.get(3, 0), light.get(3, 1), light.get(3, 2), light.get(3, 3));
	
}

void Window::praiseTheSun(){
	
	if (sunX < 0){
		toggle = 1;
	}
	if (sunX > 1024){
		toggle = -1;
	}
	sunX = sunX + (10.0*toggle);
	sunY = (-0.001*(sunX - 512.0)*(sunX - 512.0))+300.0;

	sphere_Z.makeTranslate(sunX, sunY, 1020.0);
	moveSphere->setMatrix(sphere_Z);

	Vector3 yellow = Vector3(0.8, 0.8, 0.0);
	Vector3 white = Vector3(0.8, 0.8, 0.8);
	whiteness = (yellow *(1 - sunY / 300) + white * (sunY / 300)).toVector4(1.0);
	Globals::light->diffuseColor = Color(whiteness[0], whiteness[1], whiteness[2], whiteness[3]);
}





