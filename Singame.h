#pragma once

#include "GLScene.h"

#include "Camera.h"
#include "Map.h"
#include "Ball.h"


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
	Camera* m_Camera;
	QuaternionRotation	m_QuaternionRotation;
	//gameobject
	Ball aw;
	Map minGu;
	//

	// 조명
	const GLfloat AmbientLight[4] = { 1.0f, 0.0f, 0.0f, 0.5F }; // 녹색조명 
	const GLfloat DiffuseLight[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; // 적색조명 
	const GLfloat SpecularLight[4] = { 1.0, 1.0, 1.0, 1.0 }; // 백색조명 
	GLfloat lightPos[4] = { -60.0, 10.0, 0.0, 1.0 };

	GLfloat specref[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	int Specular = 60;

	//
	bool right_button_pressed{false};

	float rotation_x;
	float rotation_y;
	float rotation_z;


};

