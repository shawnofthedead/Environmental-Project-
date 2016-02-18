#ifdef _WIN32
	#include <windows.h>
#endif

#include "Rasterizer.h"
#include "Drawable.h"
#include "Color.h"
#include "Window.h"
#include "Camera.h"
#include "Globals.h"
#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>


static int window_width = Window::width;
static int window_height =  Window::height;
static float* pixels = new float[window_width * window_height * 3];
static float* z_buffer = new float[window_width * window_height];
bool Rasterizer::buffer = true;
float temp = 0.0;
float temp2 = 0.0;
float temp3 = 0.0;


Rasterizer::Rasterizer()
{
	for (int i = 0; i < window_width * window_height; i++){
		z_buffer[i] = 1.0;
	}
}


Rasterizer::~Rasterizer()
{
}

void Rasterizer::drawPoint(Vector4 v)
{
	
	Vector4 r;
	Matrix4 ci;
	ci = Globals::camera->getInverseMatrix();
	r = ci * v;
	r = P * r;
	r = r.dehomogenize();
	r = D * r;

	Color color = color.white();
	int offset = (int)r[1]*window_width * 3 + (int)r[0] * 3;

	if ( 0 < r[1] && r[1] < window_height && 0 < r[0] && r[0] < window_width)
	{
		pixels[offset] = color[0];
		pixels[offset + 1] = color[1];
		pixels[offset + 2] = color[2];
	}
}

void Rasterizer::drawTriangle(Vector3 n1, Vector3 n2, Vector3 n3, Vector4 p_1, Vector4 p_2, Vector4 p_3)
{
	Matrix4 ci;
	ci = Globals::camera->getInverseMatrix();

	Vector4 v1, v2, v3;

	// rasterize v1
	v1 = ci * p_1;
	v1 = P * v1;
	v1 = v1.dehomogenize();
	v1 = D * v1;

	// rasterize v2
	v2 = ci * p_2;
	v2 = P * v2;
	v2 = v2.dehomogenize();
	v2 = D * v2;

	// rasterize v3
	v3 = ci * p_3;
	v3 = P * v3;
	v3 = v3.dehomogenize();
	v3 = D * v3;

	

	// Compute the Bounding Box
	int lowx = min(v1[0], min(v2[0], v3[0]));
	int highx = max(v1[0], max(v2[0], v3[0]));
	if (lowx < 0){
		lowx = 0;
	}

	if (highx > window_width){
		highx = window_width;
	}

	int lowy = min(v1[1], min(v2[1], v3[1]));
	int highy = max(v1[1], max(v2[1], v3[1]));
	if (lowy < 0){
		lowy = 0;
	}

	if (highy > window_height){
		highy = window_height;
	}

	int lowz = min(v1[2], min(v2[2], v3[2]));
	int highz = max(v1[2], max(v2[2], v3[2]));
	
	
	Vector3 v_1 = v1.toVector3();
	temp = v1[2];
	v_1[2] = 0;

	Vector3 v_2 = v2.toVector3();
	temp2 = v2[2];
	v_2[2] = 0;
	
	Vector3 v_3 = v3.toVector3();
	temp3 = v3[2];
	v_3[2] = 0;
	
	// Steps through all pixels
	
	for (int x = lowx; x <= highx; x++)
	{
		for (int y = lowy; y <= highy; y++)
		{

			
			Vector3 p;
			p.set(x, y, 0);

			//n = (b - a) x (c - a)
			Vector3 n = (v_2 - v_1).cross(v_3 - v_1);
			
			//na = (c-b) x (p-b)
			Vector3 na = (v_3 - v_2).cross(p - v_2);
			
			//alpha =  (n . na) / (||n||)^2
			float alpha = n.dot(na) / (n.magnitude() * n.magnitude());

	
			//nb = (a-c) x (p-c)
			Vector3 nb = (v_1 - v_3).cross(p - v_3);
			
			//beta =  (n . nb) / (||n||)^2
			float beta = n.dot(nb) / (n.magnitude() * n.magnitude());

			//nc = (b-a) x (p-a)
			Vector3 nc = (v_2 - v_1).cross(p - v_1);

			//gamma = (n . nc) / (||n||)^2
			float gamma = n.dot(nc) / (n.magnitude() * n.magnitude());

			if (alpha >= 0.0 && alpha <= 1.0 && beta >= 0.0 && beta <= 1.0 && gamma >= 0.0 && gamma <= 1.0)
			{
				//awesome color
				Vector3 norm = n1.scale(alpha) + n2.scale(beta) + n3.scale(gamma);
				norm = norm.normalize();
				Vector3 one;
				one.set(1.0, 1.0, 1.0);
				Vector3 tricolor = (norm + one).scale(0.5);

				int trioffset = (y * window_width * 3) + (x * 3);
				int tric = (y * window_width) + x;

				if (trioffset + 2 < window_width * window_height * 3)
				{
					
					if (buffer == false)
					{
						// z- buffer

						//Vector3 point = v_1.scale(alpha) + v_2.scale(beta) + v_3.scale(gamma);
						//float z = point[2];
						float z = temp * alpha + temp2 * beta + temp3 * gamma;
						if (z < z_buffer[tric]){
							z_buffer[tric] = z;

							pixels[trioffset] = tricolor[0];
							pixels[trioffset + 1] = tricolor[1];
							pixels[trioffset + 2] = tricolor[2];

						}
					}
					else{
						pixels[trioffset] = tricolor[0];
						pixels[trioffset + 1] = tricolor[1];
						pixels[trioffset + 2] = tricolor[2];
					}
				}
			}	
			
		}
	}

}
void Rasterizer::display()
{
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// glDrawPixels writes a block of pixels to the framebuffer
	glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);

	
}

void Rasterizer::reshape(int new_width, int new_height, float aspect, float FOV)
{
	window_width = new_width;
	window_height = new_height;
	delete[] pixels;
	pixels = new float[window_width * window_height * 3];

	delete[] z_buffer;
	z_buffer = new float[window_width * window_height * 3];

	float close = 1.0;
	float further = 1000.0;
	D = D.getMatrixD(window_height, window_width);
	P = P.getMatrixP(close, further, aspect, FOV);
}

// Clear frame buffer
void Rasterizer::clearBuffer()
{
	Color clearColor = { 0.0, 0.0, 0.0 };   // clear color: black

	for (int i = 0; i < window_width * window_height; i++){
		z_buffer[i] = 1.0;
	}

	for (int i = 0; i<window_width*window_height; ++i)
	{
		Color color = color.white();
		if (i + 3 < window_width*window_height)
		{
		
			pixels[i * 3] = clearColor[0];
			pixels[i * 3 + 1] = clearColor[1];
			pixels[i * 3 + 2] = clearColor[2];
		}
	

	}
}




