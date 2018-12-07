#pragma once
#include "OBJLoader.h"

#include "Camera.h"
#include "LinearMath.h"
#include "Transformations.h"
class Ball
{
public:
	Ball();
	~Ball();
	void init();
	void Draw();
	void update(float time, std::vector<Vector3>& other, std::vector<Vector3>& otherU);
	bool Collide(std::vector<Vector3>& otherV, std::vector<Vector3>& otherUV);

	void move(int key,Camera *m_Camera);
public:
	OBJLoader a;

	Vector3 Pos{ 0,0,0 };
	Vector3 Move{ 1,1,1 };
	Vector3 Rotate_shaft{ 0,0,0 };
	Matrix4x4 ball_matrix;

	std::vector<Vector3> vertices;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;

	QuaternionRotation	m_QuaternionRotation_Z;
	QuaternionRotation	m_QuaternionRotation_X;

	float rotation_x{0};
	float rotation_z{ 0 };


	Vector3 p0{ 0,0,0 }, p1{ 0,0,1 }, p2{ 1,0,0 };

	int ballSize{ 60 };
};

