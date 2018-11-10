#include "stdafx.h"
#include "Singame.h"
#include "GLFramework.h"


Singame::Singame()
{
}


Singame::~Singame()
{
}

void Singame::init()
{
	reshape(800, 600);
}

void Singame::exit()
{
}

void Singame::reset()
{
}

void Singame::render()
{

}

void Singame::reshape(int w, int h)
{
}

void Singame::keyboard(int key, bool pressed, int x, int y, bool special)
{
	switch (key)
	{
	case VK_ESCAPE:
	{
		printf("≥≤\n¡ﬂ\nø©\n");
		break;
	}
	}
}

void Singame::mouse(int button, bool pressed, int x, int y)
{
}

void Singame::motion(bool pressed, int x, int y)
{
}

void Singame::update(float fDeltaTime)
{
}
