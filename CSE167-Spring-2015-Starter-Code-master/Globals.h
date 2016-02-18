#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "Sphere.h"				//add for extra credit
#include "House.h"				//add for pa2
#include "OBJObject.h"			//add for pa2
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Drawable.h"
#include "Matrix4.h"			//add for pa3
#include "Rasterizer.h"			//add for pa3
#include "Skybox.h"				//add for pa5
#include "Cylinder.h"			//add for pa5
#include "Group.h"				//add for pa5
#include "Robot.h"				//add for pa5
#include "Terrain.h"
#include "MatrixTransform.h"	
#include "Vector4.h"



class Globals
{
    
public:
    
    static Camera* camera;
	static Skybox* skybox;
	static Cylinder* cylinder;
	static Robot* robot;
	static Group root;
	
	

    static Cube* cube;
	static Sphere* sphere;		//add for extra credit
	static Terrain* terrain;
	static MatrixTransform* rotateWorld;
	static MatrixTransform* moveHorizontal;
	static MatrixTransform* moveVertical;

    static Light* light;
    static DrawData drawData;
    static UpdateData updateData;
    //Feel free to add more member variables as needed
	static int view;


	static Rasterizer rasterizer;
    
	static Drawable* object[7];
};

#endif
