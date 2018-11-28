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
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
}

void Singame::exit()
{
}

void Singame::reset()
{

}

void Singame::render()
{
	glPushMatrix();
	glTranslatef(0, 0, -300);
	
	glutSolidSphere(30, 100, 100);
	glPopMatrix();
}

void Singame::reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1, 1.0, 10000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Singame::keyboard(int key, bool pressed, int x, int y, bool special)
{
	switch (key)
	{
	case VK_ESCAPE:
	{
		print("≥≤\n¡ﬂ\nø©\n",0,0,1);
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
