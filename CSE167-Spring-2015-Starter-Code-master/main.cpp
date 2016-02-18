#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "GLee.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Globals.h"
#include "MathTestBench.h"


int main(int argc, char *argv[])
{
    //Math Test Bench
    MathTestBench::runTests();
    
    glutInit(&argc, argv);                                      //Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   //Open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(Window::width, Window::height);          //Set initial window size
    glutCreateWindow("UCSD CSE 167 - Project 1 - OpenGL Cube"); //Open window and set window title
    
    glEnable(GL_DEPTH_TEST);                                    //Enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT);                               //Clear depth buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);                           //Set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);                  //Set polygon drawing mode to fill front and back of each polygon
    glDisable(GL_CULL_FACE);                                    //Disable backface culling to render both sides of polygons
    glShadeModel(GL_SMOOTH);                                    //Set shading to smooth
    
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);                                //Enable color materials
    glEnable(GL_LIGHTING);                                      //Enable lighting
	glEnable(GL_TEXTURE_2D);   // enable texture mapping

	glEnable(GL_NORMALIZE);
	
	
    //Register callback functions:
    glutDisplayFunc(Window::displayCallback);
    glutReshapeFunc(Window::reshapeCallback);
    glutIdleFunc(Window::idleCallback);
    //Register the callback for the keyboard
	glutKeyboardFunc(Window::keyboardCallback);
    //Register the callback for the keyboard function keys
    //Register the callback for the mouse
	glutMouseFunc(Window::mouseCallback);
    //Register the callback for the mouse motion
	glutMotionFunc(Window::motionCallback);
    

    //Initialize the Window:
    //The body of this function is a great place to load textures, shaders, etc.
    //and do any operations/calculations/configurations that only need to happen once.
    Window::initialize();
    
    //Start up the render loop!
    glutMainLoop();
    
    return 0;
}

