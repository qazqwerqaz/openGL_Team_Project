#pragma once
class GLFramework
{
public:
	GLFramework(std::string strWinTitle = "Default Title");
	~GLFramework();

	void init(int argc, char* argv[], int WinWidth, int WinHeight, bool bFullScreen = false, int DisplayMode = GLUT_DOUBLE | GLUT_RGBA);
	
	void run();
	void draw();
	void render();
	void reshape(int w, int h);

	void keyboardDown(unsigned char key, int x, int y);
	void keyboardUp(unsigned char key, int x, int y);

	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void freeMotion(int x, int y);

	void specialDown(int key, int x, int y);
	void specialUp(int key, int x, int y);

	void update(int deltaTime);

private:

private:

	std::string			m_CurrentScene;
	std::string			m_WinTitle;

	bool				m_FullScreen{ true };
};

