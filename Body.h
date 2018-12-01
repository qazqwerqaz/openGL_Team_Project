/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* Permission to use, copy, modify, distribute and sell this software
* and its documentation for any purpose is hereby granted without fee,
* provided that the above copyright notice appear in all copies.
* Erin Catto makes no representations about the suitability 
* of this software for any purpose.  
* It is provided "as is" without express or implied warranty.
*/

#ifndef BODY_H
#define BODY_H

#include "LinearMath.h"

struct Body
{
	Body();
	void Set(const Vector2& w, float m);

	void AddForce(const Vector2& f)
	{
		force.x += f.x;
		force.y += f.y;
	}

	Vector2 position;
	float rotation;

	Vector2 velocity;
	float angularVelocity;

	Vector2 force;
	float torque;

	Vector2 width;

	float friction;
	float mass, invMass;
	float I, invI;
};

#endif
