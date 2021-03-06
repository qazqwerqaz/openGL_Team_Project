#include "stdafx.h"
#include "Singame2.h"
#include "GLFramework.h"

#include "World.h"
#include "Body.h"
#include "Joint.h"

namespace
{
	GLuint texture[1];
	OBJLoader a;

	Body bodies[200];
	Joint joints[100];

	Body* bomb = NULL;
	Body* bomb1 = NULL;
	Body* bomb2 = NULL;
	Body* bomb3 = NULL;
	Body* bomb4 = NULL;
	Body* bomb5 = NULL;
	Body* bomb6 = NULL;


	Body* Box_Ball = NULL;
	Body* wall = NULL;

	float timeStep = 1.0f / 60.0f;
	int iterations = 10;
	Vec2 gravity(0.0f, 0.0f);

	int numBodies = 0;
	int numJoints = 0;

	int demoIndex = 0;

	World world(gravity, iterations);
	Matrix4x4 curMatrix;

	float Box_size = 30;

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

		glMultMatrixf(&curMatrix);

		float y = Box_size;
		//abs(v1.x - v3.x);
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

		bomb->position.Set(100, 50);
		bomb->rotation = Random(-1.5f, 1.5f);
		bomb->velocity = 0 * bomb->position;
		bomb->angularVelocity = Random(-20.0f, 20.0f);
	}

	float Bomb_mess = 5;
	float Bomb_size = 12;
	void LaunchBomb1()
	{
		if (!bomb1)
		{
			bomb1 = bodies + numBodies;
			bomb1->Set(Vec2(Bomb_size, Bomb_size), Bomb_mess);
			bomb1->friction = 0.2f;
			world.Add(bomb1);
			++numBodies;
		}

		bomb1->position.Set(0, 100);

		bomb1->rotation = Random(-1.5f, 1.5f);
		bomb1->velocity = 0 * bomb1->position;

		bomb1->angularVelocity = Random(-20.0f, 20.0f);
	}
	void LaunchBomb2()
	{
		if (!bomb2)
		{
			bomb2 = bodies + numBodies;
			bomb2->Set(Vec2(Bomb_size, Bomb_size), Bomb_mess);
			bomb2->friction = 0.2f;
			world.Add(bomb2);
			++numBodies;
		}

		bomb2->position.Set(-15, 120);
		bomb2->rotation = Random(-1.5f, 1.5f);
		bomb2->velocity = 0 * bomb2->position;

		bomb2->angularVelocity = Random(-20.0f, 20.0f);
	}
	void LaunchBomb3()
	{
		if (!bomb3)
		{
			bomb3 = bodies + numBodies;
			bomb3->Set(Vec2(Bomb_size, Bomb_size), Bomb_mess);
			bomb3->friction = 0.2f;
			world.Add(bomb3);
			++numBodies;
		}

		bomb3->position.Set(15, 120);


		bomb3->rotation = Random(-1.5f, 1.5f);
		bomb3->velocity = 0 * bomb3->position;

		bomb3->angularVelocity = Random(-20.0f, 20.0f);
	}
	void LaunchBomb4()
	{
		if (!bomb4)
		{
			bomb4 = bodies + numBodies;
			bomb4->Set(Vec2(Bomb_size, Bomb_size), Bomb_mess);
			bomb4->friction = 0.2f;
			world.Add(bomb4);
			++numBodies;
		}

		bomb4->position.Set(0, 135);
		bomb4->rotation = Random(-1.5f, 1.5f);
		bomb4->velocity = 0 * bomb4->position;

		bomb4->angularVelocity = Random(-20.0f, 20.0f);
	}
	void LaunchBomb5()
	{
		if (!bomb5)
		{
			bomb5 = bodies + numBodies;
			bomb5->Set(Vec2(Bomb_size, Bomb_size), Bomb_mess);
			bomb5->friction = 0.2f;
			world.Add(bomb5);
			++numBodies;
		}

		bomb5->position.Set(-20, 135);
		bomb5->rotation = Random(-1.5f, 1.5f);
		bomb5->velocity = 0 * bomb5->position;

		bomb5->angularVelocity = Random(-20.0f, 20.0f);
	}

	void LaunchBomb6()
	{
		if (!bomb6)
		{
			bomb6 = bodies + numBodies;
			bomb6->Set(Vec2(Bomb_size, Bomb_size), Bomb_mess);
			bomb6->friction = 0.2f;
			world.Add(bomb6);
			++numBodies;
		}

		bomb6->position.Set(20, 135);
		bomb6->rotation = Random(-1.5f, 1.5f);
		bomb6->velocity = 0 * bomb6->position;

		bomb6->angularVelocity = Random(-20.0f, 20.0f);
	}


	void LaunchBox_Ball()
	{
		if (!Box_Ball)
		{
			Box_Ball = bodies + numBodies;
			Box_Ball->Set(Vec2(40.0f, 40.0f), 50.f);
			Box_Ball->friction = 0.2f;
			world.Add(Box_Ball);
			++numBodies;
		}

		Box_Ball->position.Set(0, 0);
		Box_Ball->rotation = Random(-1.5f, 1.5f);
		Box_Ball->velocity = -1.5f * Box_Ball->position;
		Box_Ball->angularVelocity = Random(-20.0f, 20.0f);
	}

	void LaunchBox_Wall()
	{
		if (!wall)
		{
			wall = bodies + numBodies;
			wall->Set(Vec2(30.0f, 30.0f), 50.f);
			wall->friction = 0.2f;
			world.Add(wall);
			++numBodies;
		}

		wall->position.Set(0, 0);
		wall->rotation = Random(-1.5f, 1.5f);
		wall->velocity = -1.5f * wall->position;
		wall->angularVelocity = Random(-20.0f, 20.0f);
	}

	void Demo7(Body* b, Joint* j)
	{
		b->Set(Vec2(100.0f, 20.0f), FLT_MAX);
		b->friction = 0.2f;
		b->position.Set(0.0f, -400.5f);
		b->rotation = 0.0f;
		world.Add(b);
		++b; ++numBodies;

		const int numPlanks = 50;
		float mass = 50.0f;

		for (int i = 0; i < numPlanks; ++i)
		{
			b->Set(Vec2(1.0f, 0.25f), mass);
			b->friction = 0.2f;
			b->position.Set(-100 + 4.f * i, -100.0f);
			world.Add(b);
			++b; ++numBodies;
		}

		// Tuning
		float frequencyHz = 2.0f;
		float dampingRatio = 0.1f;

		// frequency in radians
		float omega = 2.0f * k_pi * frequencyHz;

		// damping coefficient
		float d = 2.0f * mass * dampingRatio * omega;

		// spring stifness
		float k = mass * omega * omega;

		// magic formulas
		float softness = 5.0f / (d + timeStep * k);
		float biasFactor = timeStep * k / (d + timeStep * k);

		for (int i = 0; i < numPlanks; ++i)
		{
			j->Set(bodies + i, bodies + i + 1, Vec2(-100 + 4.f * i, -100.0f));
			j->softness = softness;
			j->biasFactor = biasFactor;

			world.Add(j);
			++j; ++numJoints;
		}

		j->Set(bodies + numPlanks, bodies, Vec2(-100 + 4.f * numPlanks, -100.0f));
		j->softness = softness;
		j->biasFactor = biasFactor;
		world.Add(j);
		++j; ++numJoints;

	}

	void Demo5(Body* b, Joint* j)
	{
		//벽그리기
		{
			b->Set(Vec2(1.0f, 1000.0f), FLT_MAX);
			b->friction = 0.2f;
			b->position.Set(500.0f, 0.0f * b->width.y);
			b->rotation = 0.0f;
			world.Add(b);
			++b; ++numBodies;

			b->Set(Vec2(1.0f, 1000.0f), FLT_MAX);
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

			b->Set(Vec2(1000.0f, 1.0f), FLT_MAX);
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

		//
		Demo7(bodies, joints);

	//	Demo5(bodies, joints);
	}
}
Singame2::Singame2()
{

}


Singame2::~Singame2()
{

}

void Singame2::init()
{
	InitDemo();

	m_Camera = new Camera;
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	rotation_x = 0;
	rotation_z = 0;

	m_Camera->setDistance(200.f);
	m_Camera->setPerspective(60.f, 10.f, 7000.f);
	m_Camera->setSensitivity(1.f);

	texture[0] = a.LoadTexture("Box.Bmp", 256, 256);
	glShadeModel(GL_SMOOTH);
	//위치
	aw.init();
	minGu.init();
	m_skybox.initTexture();
	LaunchBox_Ball();
}

void Singame2::exit()
{
	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	world.Clear();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	world.Clear();
	delete m_Camera;
}

void Singame2::reset()
{

}

void Singame2::render()
{
	m_Camera->ready();
	m_skybox.skybox(Vector3(m_Camera->getEye()));

	glPushMatrix();
	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
	glutSolidCube(10);
	glPopMatrix();

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, Specular);

	glPushMatrix();
	{
		Matrix4x4 a = m_QuaternionRotation.getRotationMatrix();

		glMultMatrixf(&a);

		glGetFloatv(GL_MODELVIEW_MATRIX, &curMatrix);
		aw.Draw(*Box_Ball);

		minGu.Draw();
	}
	glPopMatrix();



	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, -7.0f, -25.0f);

	world.Step(timeStep);

	for (int i = 0; i < numBodies; ++i)
		DrawBody(bodies + i);

	for (int i = 0; i < numJoints; ++i)
		DrawJoint(joints + i);

}

void Singame2::reshape(int w, int h)
{

}

void Singame2::keyboard(int key, bool pressed, int x, int y, bool special)
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
			aw.move(key, m_Camera, *Box_Ball, pressed);
			break;
		case '5':
			LaunchBomb();
			lightPos[0] += 10;
			break;
		case '2':
			lightPos[0] -= 10;
			break;
		case '1':
			lightPos[1] += 10;
			break;
		case '3':
			lightPos[1] -= 10;
			break;
		case 'r':
			LaunchBomb();
			LaunchBomb1();
			LaunchBomb2();
			LaunchBomb3();
			LaunchBomb4();
			LaunchBomb5();
			LaunchBomb6();
			LaunchBox_Ball();
			break;
		case ' ':
			World::positionCorrection = !World::positionCorrection;
			break;

		case 'n':
			m_Framework->toScene("Ingame3"); break;
			break;

		default:
			break;
		}
	else
	{
		aw.move(' ', m_Camera, *Box_Ball, pressed);
	}

}

void Singame2::mouse(int button, bool pressed, int x, int y)
{
	right_button_pressed = false;
	if (button == GLUT_RIGHT_BUTTON)
		right_button_pressed = true;
}

void Singame2::motion(bool pressed, int x, int y)
{
	ShowCursor(false);
	if (right_button_pressed)
		computeMatricesFromInputs(x, y, 's', pressed);
	else		computeMatricesFromInputs(x, y, 'w', pressed);
}

void Singame2::update(float fDeltaTime)
{
	static float timer;
	timer += fDeltaTime;
	if (timer >= 5)
	{
		//LaunchBomb();
		//LaunchBomb1();
		//LaunchBomb2();
		//LaunchBomb3();
		//LaunchBomb4();
		//LaunchBomb5();
		timer = 0;
	}
	aw.update(fDeltaTime, minGu.vertices, minGu.normals);

}

namespace {
	// Initial position : on +Z
	Vector3 position = Vector3(0, 100, 5);
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 60.f;

	float speed = 0.5f; // 3 units / second
	float mouseSpeed = 0.0005f;
}
void Singame2::computeMatricesFromInputs(int x, int y, int key, int pressed) {

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
		position = V3::add(position, direction * deltaTime * speed);
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

	m_Camera->setEye(position);
	m_Camera->setTarget(V3::add(position, direction));
	m_Camera->setUp(up);

	lightPos[0] = position.x;
	lightPos[1] = position.y;
	lightPos[2] = position.z;
	lastTime = currentTime;
}


