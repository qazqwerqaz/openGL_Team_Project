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

void Ball::update(float time , std::vector<Vector3>& other,std::vector<Vector3>& otherNormal)
{
	Pos.x -= Move.x;
	Pos.y -= Move.y; 
	Pos.z -= Move.z;
	if (Collide(other,otherNormal))
	{
		Pos.x += Move.x;
		Pos.y += Move.y;
		Pos.z += Move.z;
	}
		
}

bool Ball::Collide(std::vector<Vector3>& otherV, std::vector<Vector3>& otherNormal)
{
	static int aa = 0;
	int count = 0;
	Vector3 Vertex[3];
	for(int i=0;i<otherV.size();++i)
	{
		if (Pos.x - ballSize > otherV[i].x) continue;
		if (Pos.x + ballSize < otherV[i].x) continue;
		if (Pos.z - ballSize > otherV[i].z) continue;
		if (Pos.z + ballSize < otherV[i].z) continue;
		
		if (otherV[i].y > Pos.y)
		{

			Move.y = otherV[i].y - Pos.y;
			return true;
		}
		 
	}
	return false;
}

void Ball::move(int key,Camera *m_Camera)
{
	Vector3 shaft_x = V3::normalize(V3::cross(m_Camera->getTarget(), m_Camera->getEye()));
	Vector3 shaft_z = V3::normalize(V3::subtract(m_Camera->getTarget(), m_Camera->getEye()));

	switch (key)
	{
	case 'w':
		m_QuaternionRotation_X.rotate(3.14 / 180.f * 10, m_QuaternionRotation_X.rotatePoint({ shaft_x.x,0,shaft_x.z }));
		Pos.x += shaft_x.z;
		Pos.z -= shaft_x.x;
		break;
	case 's':
		m_QuaternionRotation_X.rotate(-3.14 / 180.f * 10, m_QuaternionRotation_X.rotatePoint({ shaft_x.x,0,shaft_x.z }));
		Pos.x -= shaft_x.z;
		Pos.z += shaft_x.x;
		break;
	case 'a':
		m_QuaternionRotation_X.rotate(3.14 / 180.f * 10, m_QuaternionRotation_X.rotatePoint({ shaft_z.x,0,shaft_z.z }));
		Pos.x -= shaft_x.x;
		Pos.z -= shaft_x.z;
		break;
	case 'd':
		m_QuaternionRotation_X.rotate(-3.14 / 180.f * 10, m_QuaternionRotation_X.rotatePoint({ shaft_z.x,0,shaft_z.z }));
		Pos.x += shaft_x.x;
		Pos.z += shaft_x.z;
		break;
	default:
		break;
	}

}


