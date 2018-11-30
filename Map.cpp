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
	a.loadOBJ("ªÍ≈∏.obj", vertices, uvs, normals);
}

void Map::Draw()
{
	glBegin(GL_TRIANGLES);
	for (auto& a : vertices)
	{
		glVertex3f(a.x, a.y, a.z);
	}
	glEnd();
}
