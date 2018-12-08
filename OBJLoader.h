#pragma once
#include "LinearMath.h"

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();

	void init();
	//OBJ �ε�
	bool loadOBJ(const char * path,
		std::vector<Vector3> & out_vertices,
		std::vector<Vector2> & out_uvs,
		std::vector<Vector3> & out_normals);

	//Texture �ε�
	void initTexture();
	GLuint LoadTexture(const char * filename, int width, int height);
	void skybox(Vector3 Eye);
	void FreeTexture(GLuint texture);
private:
	GLuint texture[7];
};

