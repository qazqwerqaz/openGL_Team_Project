#pragma once

#include"LinearMath.h"
class JY_Ball {
public:
	JY_Ball();
	~JY_Ball();

public:
	int radius;

	Vector3 Pos;
	Vector3 velocity;
};