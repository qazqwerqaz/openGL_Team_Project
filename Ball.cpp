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
	
	glColor3f(1, 0, 0);

	
	Matrix4x4 b;
	//glGetFloatv(GL_MODELVIEW_MATRIX, &ball_matrix);
	
	glPushMatrix();
	{
		//glMultMatrixf(&ball_matrix);
		glMultMatrixf(&m_QuaternionRotation_Z.getRotationMatrix());
		
		
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
	{
		Pos.x += Move.x;
		m_QuaternionRotation_Z.rotate(3.141592 / 180, m_QuaternionRotation_Z.rotatePoint(V3::add(Rotate_shaft, { 0,0,1 })));
	}
		break;
	case 's':
	{
		Pos.x -= Move.x;
		m_QuaternionRotation_Z.rotate(-3.141592 / 180, m_QuaternionRotation_Z.rotatePoint(V3::add(Rotate_shaft, { 0,0,1 })));
	}
		break;
	case 'a':
	{
		Pos.z += Move.z;
		m_QuaternionRotation_Z.rotate(3.141592 / 180, m_QuaternionRotation_Z.rotatePoint(V3::add(Rotate_shaft, { 1,0,0 })));
	}
		break;
	case 'd':
	{
		Pos.z -= Move.z;
		m_QuaternionRotation_Z.rotate(-3.141592 / 180, m_QuaternionRotation_Z.rotatePoint(V3::add(Rotate_shaft, { 1,0,0 })));
	}
		break;
	default:
		break;
	}

}


