#include"stdafx.h"

#include "Map.h"



Map::Map()
{
}


Map::~Map()
{
}

void Map::init()
{
	a.initTexture();
	a.loadOBJ("ªÍ≈∏µÈ.obj", vertices, uvs, normals);
	
	//glTranslatef(0, 200, 0);
}

void Map::Draw()
{
	glEnable(GL_TEXTURE_2D); 
	a.skybox();

	glColor3f(0.0, 1.0, 0.5);
	glBegin(GL_TRIANGLES);
	for (auto& a : vertices)
	{
		glNormal3f(0,1, 0);
		glVertex3f(a.x, a.y, a.z);
	}
	glEnd();
	glColor3f(1,1,1);

}

void Map::Collide()
{
	
}
