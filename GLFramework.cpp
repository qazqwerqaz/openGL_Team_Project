#include "stdafx.h"
#include "GLFramework.h"
#ifndef _SCENES_
#include "GLScenesInfo.h"
#endif

GLFramework::GLFramework(std::string strWinTitle)
{
	m_WinTitle = strWinTitle;
}


GLFramework::~GLFramework()
{

}

void GLFramework::init(int argc, char * argv[], int WinWidth, int WinHeight, bool bFullScreen, int DisplayMode)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(
		(glutGet(GLUT_SCREEN_WIDTH) - WinWidth) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - WinHeight) / 2
	);
	glutCreateWindow(m_WinTitle.c_str());

	//m_Framework = this;

	if (bFullScreen)
		glutFullScreen();

	/*for (auto scene : SCENES)
		addScene(scene.name, scene.pScene, scene.bInitAtStart);
	toScene(STARTING_SCENE);*/
}

void GLFramework::run()
{
	glutMainLoop();
}

void GLFramework::draw()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	render();

	glutSwapBuffers();
}

void GLFramework::render()
{
	if (m_Scenes[m_CurrentScene])
		m_Scenes[m_CurrentScene]->render();
}

void GLFramework::reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int d = (w > h) ? w : h;
	glOrtho(0, w, h, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	if (m_Scenes[m_CurrentScene])
		m_Scenes[m_CurrentScene]->reshape(w, h);
	glutPostRedisplay();
}

void GLFramework::keyboardDown(unsigned char key, int x, int y)
{

}

void GLFramework::keyboardUp(unsigned char key, int x, int y)
{
}

void GLFramework::mouse(int button, int state, int x, int y)
{
}

void GLFramework::motion(int x, int y)
{
}

void GLFramework::freeMotion(int x, int y)
{
}

void GLFramework::specialDown(int key, int x, int y)
{
}

void GLFramework::specialUp(int key, int x, int y)
{
}

void GLFramework::update(int deltaTime)
{
}

