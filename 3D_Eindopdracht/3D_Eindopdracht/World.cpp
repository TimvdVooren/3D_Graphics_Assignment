#include "World.h"
#include "GL/freeglut.h"
#include "FloorComponent.h"

static World* world;
struct Camera
{
	float posX = 0;
	float posY = 0;
	float rotX = 0;
	float rotY = 0;
	float posZ = -4;
} camera;

World::World(int horizontal, int vertical)
{
	world = this;
	width = horizontal;
	height = vertical;
	lastFrameTime = 0;
	glEnable(GL_DEPTH_TEST);
	ZeroMemory(keys, sizeof(keys));

	createFloor();
}

World::~World()
{
	delete world;
}

void World::idle(void)
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	const float speed = 3;
	if (keys['A'] || keys['a']) move(0, deltaTime*speed);
	if (keys['D'] || keys['d']) move(180, deltaTime*speed);
	if (keys['W'] || keys['w']) move(90, deltaTime*speed);
	if (keys['S'] || keys['s']) move(270, deltaTime*speed);
	if (keys['Q'] || keys['q']) camera.posZ += deltaTime * speed;
	if (keys['E'] || keys['e']) camera.posZ -= deltaTime * speed;

	glutPostRedisplay();
}

void World::display()
{
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, width / (float)height, 0.1f, 500.0f);

	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posZ, camera.posY);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (GameObject* object : gameObjects) {
		glPushMatrix();
		object->draw();
		glPopMatrix();
	}

	//spawns a cube
	spawnCube(1, 1, 1, 2);

	glutSwapBuffers();
}

void World::reshape(int horizontal, int vertical)
{
	width = horizontal;
	height = vertical;
}

void World::move(float angle, float fac)
{
	camera.posX += cosf((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += sinf((camera.rotY + angle) / 180 * M_PI) * fac;
}

void World::keyboard(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;
		default:
			break;
	}
	keys[key] = true;
}

void World::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	keys[key] = false;
}

void World::mousePassiveMotion(int x, int y)
{
	int dx = x - width / 2;
	int dy = y - height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400 && !justMovedMouse)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
	}
	if (!justMovedMouse)
	{
		glutWarpPointer(width / 2, height / 2);
		justMovedMouse = true;
	}
	else
		justMovedMouse = false;
}

void World::mouseClick(int button, int state, int x, int y)
{
}

World * World::getWorld()
{
	return world;
}

void World::createFloor()
{
	GameObject* floor = new GameObject();
	floor->addComponent(new FloorComponent());
	gameObjects.push_back(floor);
}

void World::spawnCube(float x, float y, float z, float size)
{
	glTranslatef(x, y, z);
	glScalef(size, size, size);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	//front
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);

	//back
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);

	//top
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);

	//bottom
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);

	//left
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(0, 0, 1);

	//right
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 0, 1);
	glEnd();
}
