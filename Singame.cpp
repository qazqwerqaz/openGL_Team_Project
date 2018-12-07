#include "stdafx.h"
#include "Singame.h"
#include "GLFramework.h"

#include "World.h"
#include "Body.h"
#include "Joint.h"


Body bodies[200];
Joint joints[100];

Body* bomb = NULL;

float timeStep = 1.0f / 60.0f;
int iterations = 10;
Vec2 gravity(0.0f, 0.0f);

int numBodies = 0;
int numJoints = 0;

int demoIndex = 0;

World world(gravity, iterations);
Matrix4x4 curMatrix;

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
	glBegin(GL_LINE_LOOP);
	glVertex3f(v1.x, v1.y, 0.0f);
	glVertex3f(v2.x, v2.y, 0.0f);
	glVertex3f(v3.x, v3.y, 0.0f);
	glVertex3f(v4.x, v4.y, 0.0f);
	glEnd();

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
	glVertex3f(x1.x, x1.y, 0.0f);
	glVertex3f(p1.x, p1.y, 0.0f);
	glVertex3f(x2.x, x2.y, 0.0f);
	glVertex3f(p2.x, p2.y, 0.0f);
	glEnd();

	glPopMatrix();
}

void LaunchBomb()
{
	if (!bomb)
	{
		bomb = bodies + numBodies;
		bomb->Set(Vec2(1.0f, 1.0f), 50.0f);
		bomb->friction = 0.2f;
		world.Add(bomb);
		++numBodies;
	}

	bomb->position.Set(Random(-15.0f, 15.0f), 15.0f);
	bomb->rotation = Random(-1.5f, 1.5f);
	bomb->velocity = -1.5f * bomb->position;
	bomb->angularVelocity = Random(-20.0f, 20.0f);
}

void Demo5(Body* b, Joint* j)
{
	b->Set(Vec2(100.0f, 20.0f), FLT_MAX);
	b->friction = 0.2f;
	b->position.Set(0.0f, -0.5f * b->width.y);
	b->rotation = 0.0f;
	world.Add(b);
	++b; ++numBodies;

	Vec2 x(-6.0f, 0.75f);
	Vec2 y;

	for (int i = 0; i < 12; ++i)
	{
		y = x;

		for (int j = i; j < 12; ++j)
		{
			b->Set(Vec2(1.0f, 1.0f), 10.0f);
			b->friction = 0.2f;
			b->position = y;
			world.Add(b);
			++b; ++numBodies;

			y += Vec2(1.125f, 0.0f);
		}

		//x += Vec2(0.5625f, 1.125f);
		x += Vec2(0.5625f, 2.0f);
	}
}

void InitDemo()
{
	world.Clear();
	numBodies = 0;
	numJoints = 0;
	bomb = NULL;

	Demo5(bodies, joints);
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
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	rotation_x = 0;
	rotation_z = 0;

	m_Camera->setDistance(200.f);
	m_Camera->setPerspective(60.f, 10.f, 3500.f);
	m_Camera->setSensitivity(1.f);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);

	 //À§Ä¡
	aw.init();
	minGu.init();
	

}

void Singame::exit()
{
	delete m_Camera;
}

void Singame::reset()
{

}

void Singame::render()
{
	m_Camera->ready();
	

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	


	glPushMatrix();
	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
	glutSolidCube(10);
	glPopMatrix();

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, Specular);

	glPushMatrix(); 
	Matrix4x4 a = m_QuaternionRotation.getRotationMatrix();

	glMultMatrixf(&a);

	glGetFloatv(GL_MODELVIEW_MATRIX,&curMatrix);
	aw.Draw();
	minGu.Draw();
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
		//case 'w':
		//	m_QuaternionRotation.rotate(rotation_x++ * 3.14 / 180.f, { 1,0,0 });
		//	break;
		//case 's':
		//	m_QuaternionRotation.rotate(rotation_x--* 3.14 / 180.f, { 1,0,0 });
		//	break;
		//case 'a':
		//	m_QuaternionRotation.rotate(rotation_z++* 3.14 / 180.f, { 0,0,1 });
		//	break;
		//case 'd':
		//	m_QuaternionRotation.rotate(rotation_z--* 3.14 / 180.f, { 0,0,1 });
		//	break;
		case 'w':
		case 's':
		case 'a':
		case 'd':
			aw.move(key, m_Camera);
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
		default:
			break;
		}

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
	if (right_button_pressed)
		computeMatricesFromInputs(x, y, 's', pressed);
	else		computeMatricesFromInputs(x, y, 'w', pressed);
}

void Singame::update(float fDeltaTime)
{
	aw.update(fDeltaTime, minGu.vertices, minGu.normals);
}


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


