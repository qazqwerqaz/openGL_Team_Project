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
	int count = 0;
	glBegin(GL_TRIANGLES);
	for (auto& a : vertices)
	{
		count++;
		if (count == 2);
		{
			Vector3 b = V3::normalize(a);
			glNormal3f(0,1, 0);
			count == 0;
		}

		glVertex3f(a.x, a.y, a.z);
	}
	glEnd();
}
