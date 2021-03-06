#include"stdafx.h"

#include "Ball.h"



Ball::Ball()
{

}


Ball::~Ball()
{
}

GLuint texture[1];
OBJLoader a;

void Ball::init()
{
	a.initTexture();
	//a.loadOBJ("Ball.obj", vertices, uvs, normals);

	texture[0] = a.LoadTexture("Ball.bmp", 256, 256);
	for (auto& a : vertices)
	{
		a.x *= 3; a.y *= 3, a.z *= 3;
	}
}

void Ball::Draw(Body& Box_Ball)
{
	glPushMatrix();
	glTranslatef(Box_Ball.position.x, Pos.y - 10, Box_Ball.position.y);
	glColor3f(1, 0, 0);

	glPushMatrix();
	{
		glMultMatrixf(&m_QuaternionRotation_X.getRotationMatrix());
		{
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			glColor3f(1, 1, 1);
			glutSolidSphere(20, 30, 30);
			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
		}
		glColor3f(0, 0, 0);
		glutWireSphere(20, 10, 30);
	}
	glPopMatrix();
	glEnd();
	glPopMatrix();
	glColor3f(1, 1, 1);
}

void Ball::update(float time, std::vector<Vector3>& other, std::vector<Vector3>& otherNormal)
{
	if (Sound == 1)
	{
		if (Count == 0)
			sndPlaySound(L"Soil.wav", SND_ASYNC);
		Count += time;
		if (Count > 1.79)
		{
			Count = 0;
			Sound = 0;
		}
	}
	bool m_Collide = false;

	Pos.x += Move.x;
	Pos.y += Move.y;
	Pos.z += Move.z;

	if (-500 > Pos.x) m_Collide = true;
	if (500 < Pos.x)  m_Collide = true;
	if (-500 > Pos.z) m_Collide = true;
	if (500 < Pos.z)  m_Collide = true;

	if (m_Collide)
	{
		Pos.x -= Move.x;
		Pos.y -= Move.y;
		Pos.z -= Move.z;
	}



}

bool Ball::Collide(std::vector<Vector3>& otherV, std::vector<Vector3>& otherNormal)
{
	static int aa = 0;
	int count = 0;
	Vector3 Vertex[3];
	for (int i = 0; i < otherV.size(); ++i)
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

void Ball::move(int key, Camera *m_Camera, Body& Box_Ball, bool pressed)
{
	Vector3 shaft_z = V3::normalize(V3::subtract(m_Camera->getEye(), m_Camera->getTarget()));
	Vector3 shaft_x = V3::normalize(Vector3(shaft_z.z, 0, -shaft_z.x));
	
		switch (key)
		{
		case 'w':
			m_QuaternionRotation_X.rotate(3.14 / 180.f * 20, m_QuaternionRotation_X.rotatePoint({ shaft_x.x,0,shaft_x.z }));
			Box_Ball.velocity.x += shaft_x.z * 5;
			Box_Ball.velocity.y -= shaft_x.x * 5;
			if (Sound == 0)
				Sound = 1;
			break;
		case 's':
			m_QuaternionRotation_X.rotate(-3.14 / 180.f * 20, m_QuaternionRotation_X.rotatePoint({ shaft_x.x,0,shaft_x.z }));
			Box_Ball.velocity.x -= shaft_x.z * 5;
			Box_Ball.velocity.y += shaft_x.x * 5;
			if (Sound == 0)
				Sound = 1;
			break;
		case 'a':
			m_QuaternionRotation_X.rotate(-3.14 / 180.f * 20, m_QuaternionRotation_X.rotatePoint({ shaft_z.x,0,shaft_z.z }));
			Box_Ball.velocity.x -= shaft_x.x * 5;
			Box_Ball.velocity.y -= shaft_x.z * 5;
			if (Sound == 0)
				Sound = 1;
			break;
		case 'd':
			m_QuaternionRotation_X.rotate(3.14 / 180.f * 20, m_QuaternionRotation_X.rotatePoint({ shaft_z.x,0,shaft_z.z }));
			Box_Ball.velocity.x += shaft_x.x * 5;
			Box_Ball.velocity.y += shaft_x.z * 5;
			if (Sound == 0)
				Sound = 1;
			break;
		case ' ':

			break;
		case 'i':
			Pos.x = 0;
			Pos.y = 0;
			Pos.z = 0;
			break;
		default:
			break;
		}

	aaa::Clamp(Move.x, 0.f, 0.5f);
	aaa::Clamp(Move.y, 0.f, 0.f);
	aaa::Clamp(Move.z, 0.f, 0.5f);
}


