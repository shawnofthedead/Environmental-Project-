#include "Texture.h"

#include "GLee.h"
#include "Terrain.h"
#include "Window.h"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif




Terrain::Terrain()
{
	
	tempmap = new unsigned char[1024 * 1024 * 3];
	//heightmapvector = Vector3[1024 * 1024];
	//normalvector = Vector3[1024 * 1024];
	initialize();
	normalCalculation();
	
}


Terrain::~Terrain()
{
}

void Terrain::initialize(){
	int height = 1024;
	int width = 1024;
	tempmap = loadPPM("SanDiegoTerrain.ppm", height, width);

	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			Vector3 v;

			v[0] = i;
			v[2] = j;

			v[1] = tempmap[(j*width + i)*3];
			heightmapvector[i][j] = v;
		
			
		}

	}

}

float Terrain::calculatePeak(){

	//finding peak
	float peak = 0.0;
	for (int x = 0; x < 1024; x++){
		for (int y = 0; y < 1024; y++){
			if (heightmapvector[x][y][1]* Window::exY > peak)
				peak = heightmapvector[x][y][1]* Window::exY;
		}
	}
	return peak;

}

void Terrain::render(){

	

	material.apply();
	if (Window::flag == true){
		waterlevel->bind();
		float peak = calculatePeak();
		GLint uniformID = glGetUniformLocationARB(waterlevel->getPid(), "myShaderVar");
		glUniform1f(uniformID, Window::flood);
		GLint uniformWhite = glGetUniformLocationARB(waterlevel->getPid(), "myShaderWhite");
		glUniform1f(uniformWhite, peak);
		GLint uniformGrey = glGetUniformLocationARB(waterlevel->getPid(), "myShaderGrey");
		glUniform1f(uniformGrey, (Window::flood + 0.75*(peak - Window::flood)));
		GLint uniformGreen = glGetUniformLocationARB(waterlevel->getPid(), "myShaderGreen");
		glUniform1f(uniformGreen, (Window::flood + 0.5*(peak - Window::flood)));
		GLint uniformYellow = glGetUniformLocationARB(waterlevel->getPid(), "myShaderYellow");
		glUniform1f(uniformYellow, (Window::flood + 0.25*(peak - Window::flood)));
	}
	for (int x = 0; x < 1023; x++){
		
		glBegin(GL_TRIANGLE_STRIP);
		for (int y = 0; y < 1023; y++){
			
			/*glNormal3f(normalvector[y* 1024 + x][0], normalvector[y* 1024 +x][1]* Window::exY, normalvector[y* 1024 +x][2]);
			glVertex3f(heightmapvector[y* 1024 + x][0], heightmapvector[y* 1024 + x][1]* Window::exY, heightmapvector[y* 1024 + x][2]);
			glNormal3f(normalvector[(y+1)* 1024 + x][0], normalvector[(y+1)* 1024 + x][1]* Window::exY, normalvector[(y+1)* 1024 + x][2]);
			glVertex3f(heightmapvector[(y+1)* 1024 + x][0], heightmapvector[(y+1)* 1024 + x][1]* Window::exY, heightmapvector[(y+1)* 1024 + x][2]);*/
			glNormal3f(normalvector[x][y][0], normalvector[x][y][1] * Window::exY, normalvector[x][y][2]);
			glVertex3f(heightmapvector[x][y][0], heightmapvector[x][y][1] * Window::exY, heightmapvector[x][y][2]);
			glNormal3f(normalvector[x+1][y][0], normalvector[x+1][y][1] * Window::exY, normalvector[x+1][y][2]);
			glVertex3f(heightmapvector[x+1][y][0], heightmapvector[x+1][y][1] * Window::exY, heightmapvector[x+1][y][2]);

					
		}
		glEnd();
		
	}
	waterlevel->unbind();

}

unsigned char* Terrain::loadPPM(const char* filename, int& width, int& height)
{
	const int BUFSIZE = 128;
	FILE* fp;
	size_t read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;

	//Open the texture file
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}

	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);

	// Read width and height:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');

	retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width = atoi(buf[1]);
	height = atoi(buf[2]);

	// Read maxval:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');

	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);
	if (read != 1)
	{
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;
		return NULL;
	}

	return rawData;
}

void Terrain::normalCalculation(){
	Vector3 n_top, n_bottom;
	for (int x = 0; x < 1024; x++){
		for (int y = 0; y < 1024; y++){
			Vector3 v1 = heightmapvector[x][y];
			Vector3 v2 = heightmapvector[x][y + 1];
			Vector3 v3 = heightmapvector[x + 1][y];
			Vector3 v4 = heightmapvector[x + 1][y + 1];
			if (y % 2 == 0){
				
				n_top = (v3 - v2).cross(v1 - v2);
				n_top = n_top.normalize();
				normalvector[x][y] = n_top;
			}
			else if (y % 2 == 1){

				n_bottom = (v2 - v3).cross(v4 - v3);
				n_bottom = n_bottom.normalize();
				normalvector[x][y] = n_bottom;
			}
		}
	}

}

void Terrain::update(UpdateData& data){
	//
}

void Terrain::loadShader(){
	waterlevel = new Shader("diffuse_only.vert", "diffuse_only.frag", true);

}