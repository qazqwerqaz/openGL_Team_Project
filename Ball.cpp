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
		if (Pos.x - 20 > a.x) continue;
		if (Pos.x + 20 < a.x) continue;
		if (Pos.z - 20 > a.z) continue;
		if (Pos.z + 20 < a.z) continue;

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
		Pos.x += 1;
		break;
	case 's':
		Pos.x -= 1;
		break;
	case 'a':
		Pos.z += 1;
		break;
	case 'd':
		Pos.z -= 1;
		break;
	default:
		break;
	}

}


