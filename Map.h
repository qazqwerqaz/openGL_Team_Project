#pragma once
#include "OBJLoader.h"
class Map
{
public:
	Map();
	~Map();

	void init();

	void Draw();

private:
	OBJLoader a;

	std::vector<Vector3> vertices;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;
};

