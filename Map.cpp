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
	glEnable(GL_NORMALIZE);
	glBegin(GL_TRIANGLES);
	for (auto& a : vertices)
	{
		Vector3 b = V3::normalize(a);
		glNormal3f(b.x, b.y, b.z);
		glVertex3f(a.x, a.y, a.z);
	}
	glEnd();
}
