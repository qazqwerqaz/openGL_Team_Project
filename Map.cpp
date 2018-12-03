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
	a.loadOBJ("��Ÿ.obj", vertices, uvs, normals);
}

void Map::Draw()
{
	glEnable(GL_TEXTURE_2D); 
	a.skybox();

	glBegin(GL_TRIANGLES);
	for (auto& a : vertices)
	{
		glNormal3f(0,1, 0);
		glVertex3f(a.x, a.y, a.z);
	}
	glEnd();
}

void Map::Collide()
{
	
}
