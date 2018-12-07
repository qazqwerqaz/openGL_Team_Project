#pragma once


#include"JY_Ball.h"
class JY_World {
public:
	JY_World();
	~JY_World();

	void insert(JY_Ball a);

	void collision();

	void Step(float time);
public:
	std::list<JY_Ball> Ball;

	Vector3 m_gravity;
};