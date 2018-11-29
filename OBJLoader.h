#pragma once
#include "LinearMath.h"

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();
	bool loadOBJ(const char * path,
		std::vector<Vector3> & out_vertices,
		std::vector<Vector2> & out_uvs,
		std::vector<Vector3> & out_normals);
};

