#ifndef CSE167_Window_h
#define CSE167_Window_h

#include "Vector3.h"
#include "Vector4.h"
#include "MatrixTransform.h"
#include "Matrix4.h"

class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size

	static bool flag;						// -- toggle flag
	static bool ball;						// -- ball flag
	static bool rasterize_switch;			// switch between openGL and my own software rasterizer
	static bool pt_tri;						// switch between drawPoint and drawTriangle
	static float view;
	static float scale, lrmove, udmove, rotate, fbmove, degree,degreeX, degreeY, sunX, sunY, exY, flood;
	static Vector4 whiteness;
	
	
	
	

    
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	
	static void keyboardCallback(unsigned char, int, int);
	static void mouseCallback(int, int, int, int);

	static void motionCallback(int, int);
	static Vector3 trackBallMapping(int, int);
	static void lightCalculation();
	static void praiseTheSun();

};

#endif

