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
	m_Camera = new Camera;
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	rotation_x = 0;
	rotation_z = 0;

	m_Camera->setDistance(200.f);
	m_Camera->setPerspective(60.f, 10.f, 3500.f);
	m_Camera->setSensitivity(1.f);

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
	
	glPushMatrix();
	glTranslatef(0, 0, -200);
	Matrix4x4 a = m_QuaternionRotation.getRotationMatrix();

	glMultMatrixf(&a);
	glPopMatrix();
	
	aw.Draw();
	minGu.Draw();


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
			m_QuaternionRotation.rotate(rotation_x++ * 3.14 / 180.f, { 1,0,0 });
			break;
		case 's':
			m_QuaternionRotation.rotate(rotation_x--* 3.14 / 180.f, { 1,0,0 });
			break;
		case 'a':
			m_QuaternionRotation.rotate(rotation_z++* 3.14 / 180.f, { 0,0,1 });
			break;
		case 'd':
			m_QuaternionRotation.rotate(rotation_z--* 3.14 / 180.f, { 0,0,1 });
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
float mouseSpeed = 0.001f;

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

	lastTime = currentTime;
}


