#include "World.h"
#include "GL/freeglut.h"
#include "FloorComponent.h"
#include "WallComponent.h"
#include "DoorComponent.h"
#include "HedgeComponent.h"
#include "ModelComponent.h"

static World* world;
struct Camera
{
	float posX = 0;
	float posY = -3;
	float posZ = -18;
	float rotX = 0;
	float rotY = 0;
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
	createOuterWalls();
	createDoor(0, 0, GREEN);
	createHedge(-12, 0, 0, 0);
	createHedge(2, 0, 10, 0);
	createKey(0, 0, BLUE);
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
	if (keys['Q'] || keys['q']) camera.posY += deltaTime * speed;
	if (keys['E'] || keys['e']) camera.posY -= deltaTime * speed;

	for (GameObject* object : gameObjects) {
		object->update(deltaTime);
	}

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
	glTranslatef(camera.posX, camera.posY, camera.posZ);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (GameObject* object : gameObjects) {
		glPushMatrix();
		object->draw();
		glPopMatrix();
	}

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
	camera.posZ += sinf((camera.rotY + angle) / 180 * M_PI) * fac;
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (GameObject* object : gameObjects) {
			object->handleEvent(deltaTime);
		}
	}
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

void World::createOuterWalls()
{
	GameObject* outerWalls = new GameObject();
	outerWalls->addComponent(new WallComponent(-20, -20, 20, -20));
	outerWalls->addComponent(new WallComponent(20, -20, 20, 20));
	outerWalls->addComponent(new WallComponent(20, 20, -20, 20));
	outerWalls->addComponent(new WallComponent(-20, 20, -20, -20));
	gameObjects.push_back(outerWalls);
}

void World::createDoor(float x, float z, Color color)
{
	GameObject* door = new GameObject();
	DoorComponent* doorComponent = new DoorComponent(x, z, color);
	doorComponent->setGameObject(door);
	door->addComponent(doorComponent);
	gameObjects.push_back(door);
}

void World::createHedge(float startX, float startZ, float endX, float endZ)
{
	GameObject* hedge = new GameObject();
	hedge->addComponent(new HedgeComponent(startX, startZ, endX, endZ));
	gameObjects.push_back(hedge);
}

void World::createKey(float x, float z, Color color)
{
	GameObject* key = new GameObject();
	key->addComponent(new ModelComponent("Models/key.obj", x, z, color));
	gameObjects.push_back(key);
}

