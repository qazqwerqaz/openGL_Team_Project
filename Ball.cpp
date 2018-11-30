#include"stdafx.h"

#include "Ball.h"



Ball::Ball()
{
	
}


Ball::~Ball()
{
}

void Ball::init()
{
	a.initTexture();
	a.loadOBJ("Ball.obj", vertices, uvs, normals);
}

void Ball::Draw()
{

	glBegin(GL_TRIANGLES);
	for (auto& a : vertices)
	{
		glVertex3f(a.x, a.y, a.z);
	}
	glEnd();
}
