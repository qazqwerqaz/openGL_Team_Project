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
	a.loadOBJ("¹Ù´Ú.obj", vertices, uvs, normals);
}

void Map::Draw()
{
	glEnable(GL_TEXTURE_2D); 
	a.skybox();

	glColor3f(1, 0, 0);

	//glBegin(GL_TRIANGLES);
	for (auto& a : vertices)
	{
		//glNormal3f(0,1, 0);
		//glVertex3f(a.x, a.y, a.z);

		glPushMatrix();

		glTranslatef(a.x, a.y, a.z);
		glutSolidCube(5);
		glPopMatrix();
	}
	//glEnd();
	glColor3f(1,1,1);

}

void Map::Collide()
{
	
}
