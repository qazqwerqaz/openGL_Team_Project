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
	void update(float time, std::vector<Vector3>& other);
	bool Collide(std::vector<Vector3>& other);

	void move(int key);
private:
	OBJLoader a;

	Vector3 Pos{ 0,0,0 };
	Vector3 Move{ 1,1,1 };

	std::vector<Vector3> vertices;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;


	Vector3 p0{ 0,0,0 }, p1{ 0,0,1 }, p2{ 1,0,0 };

	int ballSize{ 20 };
};

