#pragma once

#include "GLScene.h"

#include "Camera.h"
#include "Map.h"
#include "Ball.h"
#include "OBJLoader.h"


class Singame:
	public GLScene
{
public:
	Singame();
	virtual ~Singame();

	virtual void init();
	virtual void exit();
	virtual void reset();
	virtual void render();
	virtual void reshape(int w, int h);
	virtual void keyboard(int key, bool pressed, int x, int y, bool special);
	virtual void mouse(int button, bool pressed, int x, int y);
	virtual void motion(bool pressed, int x, int y);
	virtual void update(float fDeltaTime);

	void computeMatricesFromInputs(int x, int y, int key, int pressed);


private:
	OBJLoader m_skybox;
	Camera* m_Camera;
	QuaternionRotation	m_QuaternionRotation;
	//gameobject
	Ball aw;
	Map minGu;
	//

	// 조명
	const GLfloat AmbientLight[4] = { 1.0f, 1.0f, 1.0f, 1.0F }; // 녹색조명 
	const GLfloat DiffuseLight[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 적색조명 
	const GLfloat SpecularLight[4] = { 1.0, 1.0, 1.0, 1.0 }; // 백색조명 
	GLfloat lightPos[4] = { -60.0, 10.0, 0.0, 1.0 };

	GLfloat Ambient[4] = { 0.25,0.25,0.25,1 };
	GLfloat Diffuse[4] = { 1.0f,1.f,1.f,1 };
	GLfloat SpecularL[4] = { 1,1,1,1 };

	GLfloat specref[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	int Specular = 60;

	//
	bool right_button_pressed{false};

	float rotation_x;
	float rotation_y;
	float rotation_z;


};

