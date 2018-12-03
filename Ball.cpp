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
	glPushMatrix();
	glTranslatef(Pos.x, Pos.y, Pos.z);
	glBegin(GL_TRIANGLES);
	for (auto& a : vertices)
	{
		glVertex3f(a.x, a.y, a.z);
	}
	glEnd();
	glPopMatrix();
}

void Ball::update(float time , std::vector<Vector3>& other)
{
	Pos.y -= Move.y;
	if (Collide(other))
		Pos.y += Move.y;
		
}

bool Ball::Collide(std::vector<Vector3>& other)
{
	for (auto& a : other)
	{
		if (Pos.x - ballSize > a.x) continue;
		if (Pos.x + ballSize < a.x) continue;
		if (Pos.z - ballSize > a.z) continue;
		if (Pos.z + ballSize < a.z) continue;

		if (a.y > Pos.y)
		{
			Move.y = a.y - Pos.y;
			return true;
		}
	}
	return false;
}

void Ball::move(int key)
{
	switch (key)
	{
	case 'w':
		Pos.x += Move.x;
		break;
	case 's':
		Pos.x -= Move.x;
		break;
	case 'a':
		Pos.z += Move.z;
		break;
	case 'd':
		Pos.z -= Move.z;
		break;
	default:
		break;
	}

}


