#pragma once

#include "GLScene.h"

#include "Camera.h"
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
	Camera* m_Camera;
	QuaternionRotation	m_QuaternionRotation;
	//�� Ŭ������ ������ �־�� �ϴ� ����
	OBJLoader a;

	std::vector<Vector3> vertices;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;

	//
	bool right_button_pressed{false};

	float rotation_x;
	float rotation_y;
	float rotation_z;


};

