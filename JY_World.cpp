#include"stdafx.h"

#include "JY_World.h"

inline float get_distance(Vector3& a, Vector3& b)
{
	return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}

JY_World::JY_World()
{
}

JY_World::~JY_World()
{
}

void JY_World::insert(JY_Ball a)
{
	Ball.push_front(a);
}

void JY_World::collision()
{
	for (auto& a : Ball)
	{
		for (auto& b : Ball)
		{
			if (get_distance(a.Pos, b.Pos) <= a.radius + b.radius)
			{
				float cosTheta = V3::dot(a.Pos, b.Pos)/(V3::size(a.Pos) * V3::size(b.Pos));
				float Radian = acos(cosTheta);
			}
		}
	}
}

void JY_World::Step(float time)
{
	for (auto& a : Ball)
	{
		a.velocity.x += m_gravity.x;
		a.velocity.y += m_gravity.y;
		a.velocity.z += m_gravity.z;
	}
}
