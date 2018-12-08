#include"stdafx.h"

#include "Map.h"
#include "Camera.h"


Map::Map()
{
}


Map::~Map()
{
}

void Map::init()
{
	a.initTexture();
	//a.loadOBJ("ªÍ≈∏.obj", vertices, uvs, normals);
}

void Map::Draw()
{
	glEnable(GL_TEXTURE_2D); 

	glColor3f(1, 0, 0);

	//glBegin(GL_TRIANGLES);
	/*glPushMatrix();
	glTranslatef(0, -100, 0);
	for (auto& a : vertices)
	{
		//glNormal3f(0,1, 0);
		//glVertex3f(a.x, a.y, a.z);

		glPushMatrix();

		glTranslatef(a.x, a.y, a.z);
		glutSolidCube(5);
		glPopMatrix();
	}
	glPopMatrix();*/

	glColor3f(1.f, 1.f, 0.f);
	glPushMatrix();
	glTranslatef(0, -45, 0);
	glScalef(1000.f, 1.f, 1000.f);
	glutSolidCube(1);

	glPopMatrix();
	//glEnd();
	glColor3f(1,1,1);

}

void Map::Collide()
{
	
}
