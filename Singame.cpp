#include "stdafx.h"
#include "Singame.h"
#include "GLFramework.h"

#include "World.h"
#include "Body.h"
#include "Joint.h"

namespace {
	GLuint texture[2];
	OBJLoader a;

	HWND hwnd;
	DWORD Music1;
	MCI_PLAY_PARMS     mciPlayParms;

	Body bodies[200];
	Joint joints[100];

	Body* bomb = NULL;

	Body* Box_Ball = NULL;

	float timeStep = 1.0f / 60.0f;
	int iterations = 10;
	Vec2 gravity(0.0f, 0.0f);

	int numBodies = 0;
	int numJoints = 0;

	int demoIndex = 0;

	World world(gravity, iterations);
	Matrix4x4 curMatrix;

	float Box_size = 30;

	bool Viewpoint = true;

	void DrawBody(Body* body)
	{
		Mat22 R(body->rotation);
		Vec2 x = body->position;
		Vec2 h = 0.5f * body->width;

		Vec2 v1 = x + R * Vec2(-h.x, -h.y);
		Vec2 v2 = x + R * Vec2(h.x, -h.y);
		Vec2 v3 = x + R * Vec2(h.x, h.y);
		Vec2 v4 = x + R * Vec2(-h.x, h.y);

		if (body == bomb)
			glColor3f(0.4f, 0.9f, 0.4f);
		else
			glColor3f(0.8f, 0.8f, 0.9f);

		glPushMatrix();
		//glLoadIdentity();
		//glutSolidCube(1);

		glPushMatrix();
		glColor3f(1, 1, 1);
		

		glPopMatrix();

		//glMultMatrixf(&curMatrix);

		float y = Box_size;
		//abs(v1.x - v3.x);
		glPushMatrix();
		glTranslatef(0, -45, 0);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-500, 1, -500);
		glTexCoord2f(0, 1); glVertex3f(-500, 1, 500);
		glTexCoord2f(1, 1); glVertex3f(500, 1, 500);
		glTexCoord2f(1, 0); glVertex3f(500, 1, -500);
		glEnd();
		glPopMatrix();

		if (body != Box_Ball)
		{

			glTranslatef(0, -10, 0);
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			glBegin(GL_QUADS);
			glTexCoord2d(1.0f, 0.0f); glVertex3f(v1.x, 0.0f, v1.y);
			glTexCoord2d(1.0f, 1.0f); glVertex3f(v2.x, 0.0f, v2.y);
			glTexCoord2d(0.0, 1.0f); glVertex3f(v3.x, 0.0f, v3.y);
			glTexCoord2d(0.0, 0.0f); glVertex3f(v4.x, 0.0f, v4.y);


			glTexCoord2d(0.0f, 1.0f); glVertex3f(v1.x, y, v1.y);
			glTexCoord2d(1.0f, 1.0f); glVertex3f(v2.x, y, v2.y);
			glTexCoord2d(1.0f, 0.0f); glVertex3f(v3.x, y, v3.y);
			glTexCoord2d(0.0f, 0.0f); glVertex3f(v4.x, y, v4.y);

			glTexCoord2d(0.0f, 1.0f); glVertex3f(v4.x, 0, v4.y);
			glTexCoord2d(0.0f, 0.0f); glVertex3f(v1.x, 0, v1.y);
			glTexCoord2d(1.0f, 0.0f); glVertex3f(v1.x, y, v1.y);
			glTexCoord2d(1.0f, 1.0f); glVertex3f(v4.x, y, v4.y);

			glTexCoord2d(0.0f, 0.0f); glVertex3f(v3.x, 0, v3.y);
			glTexCoord2d(0.0f, 1.0f); glVertex3f(v2.x, 0, v2.y);
			glTexCoord2d(1.0f, 1.0f); glVertex3f(v2.x, y, v2.y);
			glTexCoord2d(1.0f, 0.0f); glVertex3f(v3.x, y, v3.y);

			glTexCoord2d(0.0f, 1.0f); glVertex3f(v1.x, 0.0f, v1.y);
			glTexCoord2d(1.0f, 1.0f); glVertex3f(v2.x, 0.0f, v2.y);
			glTexCoord2d(1.0f, 0.0f); glVertex3f(v2.x, y, v2.y);
			glTexCoord2d(0.0f, 0.0f); glVertex3f(v1.x, y, v1.y);

			glTexCoord2d(1.0f, 0.0f); glVertex3f(v4.x, 0.0f, v4.y);
			glTexCoord2d(1.0f, 1.0f); glVertex3f(v3.x, 0.0f, v3.y);
			glTexCoord2d(0.0, 1.0f); glVertex3f(v3.x, y, v3.y);
			glTexCoord2d(0.0, 0.0f); glVertex3f(v4.x, y, v4.y);

			glEnd();
		}
		glPopMatrix();
	}

	void DrawJoint(Joint* joint)
	{
		Body* b1 = joint->body1;
		Body* b2 = joint->body2;

		Mat22 R1(b1->rotation);
		Mat22 R2(b2->rotation);

		Vec2 x1 = b1->position;
		Vec2 p1 = x1 + R1 * joint->localAnchor1;

		Vec2 x2 = b2->position;
		Vec2 p2 = x2 + R2 * joint->localAnchor2;

		glColor3f(0.5f, 0.5f, 0.8f);

		glPushMatrix();
		glMultMatrixf(&curMatrix);
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex3f(x1.x, 0.0f, x1.y);
		glVertex3f(p1.x, 0.0f, p1.y);
		glVertex3f(x2.x, 0.0f, x2.y);
		glVertex3f(p2.x, 0.0f, p2.y);
		glEnd();

		glPopMatrix();
	}

	void LaunchBomb()
	{
		if (!bomb)
		{
			bomb = bodies + numBodies;
			bomb->Set(Vec2(10.0f, 10.0f), 50.0f);
			bomb->friction = 0.2f;
			world.Add(bomb);
			++numBodies;
		}

		bomb->position.Set(Random(-400.0f, 400.0f), Random(-400.0f, 400.0f));
		bomb->rotation = Random(-1.5f, 1.5f);
		bomb->velocity = -1.5f * bomb->position;
		bomb->angularVelocity = Random(-20.0f, 20.0f);
	}

	void LaunchBox_Ball()
	{
		if (!Box_Ball)
		{
			Box_Ball = bodies + numBodies;
			Box_Ball->Set(Vec2(40.0f, 40.0f), 10);
			Box_Ball->friction = 0.2f;
			world.Add(Box_Ball);
			++numBodies;
		}

		Box_Ball->position.Set(0, 0);
		Box_Ball->rotation = Random(-1.5f, 1.5f);
		Box_Ball->velocity = -1.5f * Box_Ball->position;
		Box_Ball->angularVelocity = Random(-20.0f, 20.0f);
	}

	void Demo5(Body* b, Joint* j)
	{

		//벽그리기
		{
			b->Set(Vec2(10.0f, 1000.0f), FLT_MAX);
			b->friction = 0.2f;
			b->position.Set(500.0f, 0.0f * b->width.y);
			b->rotation = 0.0f;
			world.Add(b);
			++b; ++numBodies;

			b->Set(Vec2(10.0f, 1000.0f), FLT_MAX);
			b->friction = 0.2f;
			b->position.Set(-500.0f, 0.0f * b->width.y);
			b->rotation = 0.0f;
			world.Add(b);
			++b; ++numBodies;

			b->Set(Vec2(1000.0f, 1.0f), FLT_MAX);
			b->friction = 0.2f;
			b->position.Set(0.0f, 500.0f * b->width.y);
			b->rotation = 0.0f;
			world.Add(b);
			++b; ++numBodies;

			b->Set(Vec2(1000.0f, 10.0f), FLT_MAX);
			b->friction = 0.2f;
			b->position.Set(0.0f, -500.0f * b->width.y);
			b->rotation = 0.0f;
			world.Add(b);
			++b; ++numBodies;
		}

		Vec2 x(-6.0f, 0.75f);
		Vec2 y;


		b->Set(Vec2(Box_size, Box_size), FLT_MAX);
		b->friction = 0.5f;
		b->position = Vec2(100, 100);
		world.Add(b);
		++b; ++numBodies;

		b->Set(Vec2(Box_size, Box_size), 10.0f);
		b->friction = 0.5f;
		b->position = Vec2(200, 100);
		world.Add(b);
		++b; ++numBodies;

		b->Set(Vec2(Box_size, Box_size), 10.0f);
		b->friction = 0.5f;
		b->position = Vec2(100, 100);
		world.Add(b);
		++b; ++numBodies;



	}

	void InitDemo()
	{
		world.Clear();
		numBodies = 0;
		numJoints = 0;
		bomb = NULL;

		Demo5(bodies, joints);
	}
}
Singame::Singame()
{

}

Singame::~Singame()
{

}

void Singame::init()
{
	InitDemo();

	m_Camera = new Camera;
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	rotation_x = 0;
	rotation_z = 0;

	Music1 = a.LoadWAV(hwnd, L"Linda_March.mp3");
	texture[0] = a.LoadTexture("Box.Bmp", 256, 256);
	texture[1] = a.LoadTexture("Grass.bmp", 1024, 1024);
	m_Camera->setDistance(200.f);
	m_Camera->setPerspective(60.f, 10.f, 7000.f);
	m_Camera->setSensitivity(1.f);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_CULL_FACE);
	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);

	//위치
	aw.init();
	minGu.init();
	m_skybox.initTexture();
	LaunchBox_Ball();
}

void Singame::exit()
{
	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	//a.FreeTexture(0);
	//a.FreeTexture(1);
	world.Clear();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT1);
	delete m_Camera;
}

void Singame::reset()
{

}

void Singame::render()
{
	//RECT r;
	//ClipCursor(&r);
	Music1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms);
	m_Camera->ready();
	m_skybox.skybox(Vector3(m_Camera->getEye()));

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
	glutSolidCube(10);
	glPopMatrix();

	GLfloat ambientLight0[] = { 0.25f, 0.25f, 0.25f, 0.25f };
	GLfloat diffuseLight[] = { 1, 0.5, 0, 1 };
	GLfloat lit_spc[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPos0[] = { Box_Ball->position.x,  20,  Box_Ball->position.y, 1.0f };

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(Box_Ball->position.x, 20, Box_Ball->position.y);
	glutWireSphere(5, 25, 25);
	glPopMatrix();

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lit_spc);
	glMateriali(GL_LIGHT1, GL_SHININESS, 64);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos0);
	glEnable(GL_LIGHT1);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, Specular);

	glPushMatrix();
	{
		Matrix4x4 a = m_QuaternionRotation.getRotationMatrix();

		glMultMatrixf(&a);

		glGetFloatv(GL_MODELVIEW_MATRIX, &curMatrix);
		aw.Draw(*Box_Ball);


		world.Step(timeStep);

		for (int i = 0; i < numBodies; ++i)
			DrawBody(bodies + i);

		for (int i = 0; i < numJoints; ++i)
			DrawJoint(joints + i);

		minGu.Draw();
	}
	glPopMatrix();


	/*
	glColor3f(1, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, -7.0f, -25.0f);

	std::string str;

	str = abs(int(Box_Ball->velocity.x + Box_Ball->velocity.y));

	float count = 0.0;
	for (int s = 1; s <= 100; s *= 10)
	{
		glRasterPos2i(count, 8);
		if (count == 0.0)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[0] % 10 + 48);
		else
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (str[0] / s) % 10 + 48);

		count -= 0.5;
	}
	*/
}

void Singame::reshape(int w, int h)
{

}

void Singame::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
		switch (key)
		{
		case VK_ESCAPE:
		{
			exit();
			break;
		}
		case 'w':
		case 's':
		case 'a':
		case 'd':
			aw.move(key, m_Camera, *Box_Ball,pressed);
			break;
		case '=':
			fullmode = (fullmode + 1) % 2;
			if (fullmode == 1)
			{
				printf("FullMode On \n");
				glutFullScreen();
			}
			else
			{
				glutPositionWindow(0, 0);
				glutReshapeWindow(1200, 900);
			}
			break;
		case 'n':
			m_Framework->toScene("Ingame2"); break;
		case '1':
			Viewpoint = !Viewpoint;
			break;
		default:
			break;
		}
	else
		aw.move(' ', m_Camera, *Box_Ball, pressed);
}

void Singame::mouse(int button, bool pressed, int x, int y)
{
	right_button_pressed = false;
	if (button == GLUT_RIGHT_BUTTON)
		right_button_pressed = true;
}

void Singame::motion(bool pressed, int x, int y)
{
	ShowCursor(false);
	if (Viewpoint)
	{
		if (right_button_pressed)
			computeMatricesFromInputs(x, y, 's', pressed);
		else
			computeMatricesFromInputs(x, y, 'w', pressed);
	}
	else
		computeMatricesFromInputs(x, y, ' ', pressed);
}

void Singame::update(float fDeltaTime)
{
	static float timer;
	timer += fDeltaTime;
	if (timer >= 5)
	{
		LaunchBomb();
		timer = 0;
	}
	aw.update(fDeltaTime, minGu.vertices, minGu.normals);

}

namespace {
	// Initial position : on +Z
	Vector3 position = Vector3(0, 100, 100);
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 60.f;

	float speed = 0.5f; // 3 units / second
	float mouseSpeed = 0.0005f;

	void material0()
	{
		GLfloat ambientLight0[] = { 0.25f, 0.25f, 0.25f, 0.25f };         // 주변광의 강도
		GLfloat specref[] = { 1.0f,1.0f,1.0f,1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight0);
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambientLight0);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
		glMateriali(GL_FRONT, GL_SHININESS, 64);
		glColor3f(1, 1, 1);
		glTranslatef(0, 0, -200);
		glutSolidSphere(50, 200, 200);
	}
}
void Singame::computeMatricesFromInputs(int x, int y, int key, int pressed) {

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glutGet(GLUT_ELAPSED_TIME);


	// Compute time difference between current and last frame
	double currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos = x;
	double ypos = y;


	// Reset mouse position for next frame
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(glutGet(GLUT_WINDOW_WIDTH) / 2 - xpos);
	verticalAngle += mouseSpeed * float(glutGet(GLUT_WINDOW_HEIGHT) / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	Vector3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	Vector3 right = Vector3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	Vector3 up = V3::cross(right, direction);

	// Move forward
	if (key == 'w' && pressed) {
		position = V3::add(Vector3(0, 0, 0), V3::add(position, direction * deltaTime * speed));
	}
	// Move backward
	if (key == 's' && pressed) {
		position = V3::subtract(position, direction * deltaTime * speed);
	}
	// Strafe right
	if (key == 'd' && pressed) {
		position = V3::add(position, right * deltaTime * speed);
	}
	// Strafe left
	if (key == 'a' && pressed) {
		position = V3::subtract(position, right * deltaTime * speed);
	}

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	if (key == ' ')
	{
		m_Camera->setEye(Vector3(Box_Ball->position.x + 200 * sin(horizontalAngle), 50, Box_Ball->position.y + 200 * cos(horizontalAngle)));
		m_Camera->setTarget(Vector3(Box_Ball->position.x, 0, Box_Ball->position.y));
	}
	else
	{
		m_Camera->setEye(Vector3(Box_Ball->position.x + 300 * sin(horizontalAngle), 300, Box_Ball->position.y + 300 * cos(horizontalAngle)));
		m_Camera->setTarget(Vector3(Box_Ball->position.x, 0, Box_Ball->position.y));
	}
	//m_Camera->setTarget(V3::add(position, direction));

	//m_Camera->setUp(Vector3(0,1,0));
	//m_Camera->setUp(up);

	lightPos[0] = position.x;
	lightPos[1] = position.y;
	lightPos[2] = position.z;
	lastTime = currentTime;
}







