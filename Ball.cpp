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
	glTranslatef(Pos.x, Pos.y, Pos.z);
	glColor3f(1, 0, 0);

	glPushMatrix();
	{	
		glMultMatrixf(&m_QuaternionRotation_X.getRotationMatrix());
		
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
	int count = 0;
	Vector3 Vertex[3];
	for (auto& a : other)
	{
		//if (Pos.x - ballSize > a.x) continue;
		//if (Pos.x + ballSize < a.x) continue;
		//if (Pos.z - ballSize > a.z) continue;
		//if (Pos.z + ballSize < a.z) continue;
		//
		//if (a.y > Pos.y)
		//{
		//	//if(abs(a.y - Pos.y) < 20)
		//	Move.y = a.y - Pos.y;
		//	return true;
		//}
		Vertex[count];
		count++;
		if (count == 3)
		{
			if (Pos.x - ballSize > a.x) continue;
			if (Pos.x + ballSize < a.x) continue;
			if (Pos.z - ballSize > a.z) continue;
			if (Pos.z + ballSize < a.z) continue;


			Vector3 p0 = V3::subtract(Vertex[0], Vertex[1]);
			Vector3 p1 = V3::subtract(Vertex[2], Vertex[1]);

			Vector3 normal = V3::cross(p0, p1);

			if (normal.x*(a.x - Vertex[0].x) + normal.y*(a.y - Vertex[0].y) + normal.z*(a.z - Vertex[0].z) <= 0)
				return true;

			count = 0;
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

		m_QuaternionRotation_X.rotate(3.14 / 180.f, m_QuaternionRotation_X.rotatePoint(V3::add(Rotate_shaft, { 0,0,1 })));

		break;
	case 's':
		Pos.x -= Move.x;
		m_QuaternionRotation_X.rotate(-3.14 / 180.f, m_QuaternionRotation_X.rotatePoint(V3::add(Rotate_shaft, { 0,0,1 })));

		break;
	case 'a':
		Pos.z += Move.z;
		m_QuaternionRotation_X.rotate(-3.14 / 180.f, m_QuaternionRotation_X.rotatePoint(V3::add(Rotate_shaft, { 1,0,0 })));

		break;
	case 'd':
		Pos.z -= Move.z;
			m_QuaternionRotation_X.rotate(3.14 / 180.f, m_QuaternionRotation_X.rotatePoint(V3::add(Rotate_shaft, { 1,0,0 })));

		break;
	default:
		break;
	}

}


