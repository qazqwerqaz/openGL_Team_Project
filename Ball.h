#pragma once
#include "OBJLoader.h"

#include "LinearMath.h"
class Ball
{
public:
	Ball();
	~Ball();
	void init();
	void Draw();
	void update(float time);
	void Collide();

private:
	OBJLoader a;

	Vector3 Pos;

	std::vector<Vector3> vertices;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;
};

