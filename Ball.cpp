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

	for (auto& a : vertices)
	{
		a.x *= 3; a.y *= 3, a.z *= 3;
	}
}

void Ball::Draw()
{
	glPushMatrix();
	//glTranslatef(Pos.x, Pos.y, Pos.z);
	glColor3f(1, 0, 0);

	glPushMatrix();
	{
		Matrix4x4 a = m_QuaternionRotation.getRotationMatrix();

		glMultMatrixf(&a);

		glutSolidSphere(20, 30, 30);
		glColor3f(1, 1, 1);
		glutWireSphere(21, 30, 30);
	}
	glPopMatrix();
	glEnd();
	glPopMatrix();
	glColor3f(1, 1, 1);
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
			//if(abs(a.y - Pos.y) < 20)
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
		m_QuaternionRotation.rotate(rotation_x++ * 3.14 / 180.f, { 1,0,0 });

		break;
	case 's':
		Pos.x -= Move.x;
		m_QuaternionRotation.rotate(rotation_x++ * 3.14 / 180.f, { 1,0,0 });

		break;
	case 'a':
		Pos.z += Move.z;
		m_QuaternionRotation.rotate(rotation_z++ * 3.14 / 180.f, { 1,0,0 });

		break;
	case 'd':
		Pos.z -= Move.z;
		m_QuaternionRotation.rotate(rotation_z++ * 3.14 / 180.f, { 1,0,0 });

		break;
	default:
		break;
	}

}


