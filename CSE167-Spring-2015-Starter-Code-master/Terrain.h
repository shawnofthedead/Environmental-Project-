#ifndef CSE167_Terrain_h
#define CSE167_Terrain_h

#include "Texture.h"
#include "Geode.h"
#include "Vector3.h"
#include "Shader.h"


class Terrain : public Geode
{
public:

	Terrain();
	virtual ~Terrain();

	virtual void render();
	virtual void update(UpdateData&);

	Shader* waterlevel;
	
	void initialize();
	void loadShader();

	unsigned char* tempmap;
	Vector3 heightmapvector[1024][1024];
	Vector3 normalvector[1024][1024];

	void normalCalculation();
	float calculatePeak();

	
	


protected:
	unsigned char* Terrain::loadPPM(const char*, int&, int&);

};

#endif