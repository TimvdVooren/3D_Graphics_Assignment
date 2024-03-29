#include "World.h"
#include "GL/freeglut.h"
#include "GL/glut.h"
#include "CameraComponent.h"
#include "FloorComponent.h"
#include "WallComponent.h"
#include "DoorComponent.h"
#include "HedgeComponent.h"
#include "ModelComponent.h"
#include "LineCollisionComponent.h"
#include "CircleCollisionComponent.h"

static World* world;
std::vector<ObjColor>* collectedKeys = new std::vector<ObjColor>();

World::World(int horizontal, int vertical)
{
	world = this;
	player = new GameObject();
	CameraComponent* playerCamera = new CameraComponent();
	player->addComponent(playerCamera);
	float circleX = playerCamera->getCamera().posX;
	float circleZ = playerCamera->getCamera().posZ;
	player->addComponent(new CircleCollisionComponent(circleX, circleZ, 0.2f));
	gameObjects.push_back(player);

	width = horizontal;
	height = vertical;
	lastFrameTime = 0;
	glEnable(GL_DEPTH_TEST);
	ZeroMemory(keys, sizeof(keys));
	collectedKeys->push_back(ObjColor(NONE));
	collisionManager = new CollisionManager();

	loadWorld();
}

World::~World()
{
	delete world;
}

void World::idle(void)
{
	CameraComponent* playerCamera = dynamic_cast<CameraComponent*> (player->getComponents().at(0));

	for (GameObject* object : gameObjects) {
		object->debugging = debugging;
		collisionManager->isColliding(player, object);
		object->update(deltaTime, playerCamera->getCamera().posX, playerCamera->getCamera().posZ, collectedKeys);
	}

	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	const float speed = 3;
	if (keys['A'] || keys['a']) playerCamera->move(deltaTime*speed, WEST);
	if (keys['D'] || keys['d']) playerCamera->move(deltaTime*speed, EAST);
	if (keys['W'] || keys['w']) playerCamera->move(deltaTime*speed, NORTH);
	if (keys['S'] || keys['s']) playerCamera->move(deltaTime*speed, SOUTH);
	if (keys['Q']) playerCamera->move(deltaTime*speed, UP);
	if (keys['E']) playerCamera->move(deltaTime*speed, DOWN);

	player->isCollidingNorth = false;
	player->isCollidingEast = false;
	player->isCollidingSouth = false;
	player->isCollidingWest = false;

	glutPostRedisplay();
}

void World::display()
{
	glClearColor(0.6f, 0.6f, 0.9f, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, width / (float)height, 0.1f, 500.0f);

	GLfloat fogColor[4] = { 0.95f, 0.95f, 0.95f, 0.95f };
	glEnable(GL_FOG);
	glFogf(GL_FOG_START, 0.3f);
	glFogf(GL_FOG_END, 5.0f);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.01f);
	glHint(GL_FOG_HINT, GL_DONT_CARE);

	//Lighting messes up door colors
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat LightAmbient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);*/

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	CameraComponent* playerCamera = dynamic_cast<CameraComponent*> (player->getComponents().at(0));
	glRotatef(playerCamera->getCamera().rotX, 1, 0, 0);
	glRotatef(playerCamera->getCamera().rotY, 0, 1, 0);
	glTranslatef(playerCamera->getCamera().posX, playerCamera->getCamera().posY, playerCamera->getCamera().posZ);

	for (GameObject* object : gameObjects) {
		glPushMatrix();
		object->draw();
		glPopMatrix();
	}

	if (collectedKeys->size() == 8) {
		displayText();
	}

	glutSwapBuffers();
}

void World::reshape(int horizontal, int vertical)
{
	width = horizontal;
	height = vertical;
}

void World::keyboard(unsigned char key, int mouseX, int mouseY)
{
	if (key == 'F') {
		debugging = !debugging;
	}
	else {
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
}

void World::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	keys[key] = false;
}

void World::mousePassiveMotion(int x, int y)
{
	CameraComponent* playerCamera = dynamic_cast<CameraComponent*> (player->getComponents().at(0));
	int dx = x - width / 2;
	int dy = y - height / 2;

	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400 && !justMovedMouse)
	{
		playerCamera->rotate(dy, X);
		playerCamera->rotate(dx, Y);
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
	CameraComponent* playerCamera = dynamic_cast<CameraComponent*> (player->getComponents().at(0));
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (GameObject* object : gameObjects) {
			object->handleEvent(deltaTime, playerCamera->getCamera().posX, playerCamera->getCamera().posZ, collectedKeys);
		}
	}
}

World * World::getWorld()
{
	return world;
}

void World::displayText()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0.0, width, height, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glClear(GL_DEPTH_BUFFER_BIT);

	std::string tempString = " Congratulations You Won! ";

	glRotatef(180, 1, 0, 0);
	glLineWidth(5.0f);
	glTranslatef((width/2)-tempString.length()*17, -(height/2), 0);
	glScalef(0.5f, 0.5f, 0.5f);

	unsigned char gameoverText[256];
	std::copy(tempString.begin(), tempString.end(), gameoverText);
	gameoverText[tempString.length()] = 0;

	glutStrokeString(GLUT_STROKE_ROMAN, gameoverText);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void World::loadWorld()
{
	createFloor();
	createOuterWalls();

	//CREATES MAZE
	createHedge(12, 16, 12, 8);
	createHedge(12, 8, 8, 8);
	createHedge(8, 8, 8, 12);
	createHedge(8, 12, 0, 12);
	createHedge(-4, 16, -4, 4);
	createHedge(-4, 4, -8, 4);
	createHedge(-8, 12, -8, 8);
	createHedge(-8, 8, -12, 8);
	createHedge(-12, 8, -12, 0);
	createHedge(-12, 16, -12, 12);
	createHedge(-12, 0, 0, 0);
	createHedge(-16, -4, -8, -4);
	createHedge(-8, -4, -8, -8);
	createHedge(-8, -8, -4, -8);
	createHedge(-4, -12, -4, -0);
	createHedge(0, -8, 0, 5);
	createHedge(0, 4, 12, 4);
	createHedge(4, 4, 4, 8);
	createHedge(0, 8, 4, 8);
	createHedge(12, 4, 12, 0);
	createHedge(16, -4, 8, -4);
	createHedge(8, -4, 8, 0);
	createHedge(8, 0, 4, 0);
	createHedge(4, -4, 4, -8);
	createHedge(4, -8, 8, -8);
	createHedge(8, -8, 8, -12);
	createHedge(8, -12, -5, -12);
	createHedge(12, -4, 12, -12);
	createHedge(-8, -12, -8, -16);
	createHedge(-7, -12, -12, -12);
	createHedge(-12, -12, -12, -8);
	createHedge(12, 12, 13, 12);
	createHedge(16, 12, 15, 12);
	createHedge(0, 7, 0, 8);
	createHedge(-8, 0, -8, 1);
	createHedge(-8, 4, -8, 3);
	createHedge(-12, 12, -13, 12);
	createHedge(-16, 12, -15, 12);
	createHedge(0, -4, -1, -4);
	createHedge(-4, -4, -3, -4);
	createHedge(-12, -8, -13, -8);
	createHedge(-16, -8, -15, -8);

	//CREATES KEYS
	createKey(10, 8.5, RED);
	createKey(-2, -3.5, GREEN);
	createKey(2, 4.5, BLUE);
	createKey(-6, -7.5, PURPLE);
	createKey(14, -7.5, ORANGE);
	createKey(-14, 12.5, CYAN);

	//CREATES DOORS
	createDoor(13, 12, NONE, NORTH);
	createDoor(-1, -4, RED, SOUTH);
	createDoor(0, 5, GREEN, WEST);
	createDoor(-8, 3, BLUE, EAST);
	createDoor(-5, -12, PURPLE, SOUTH);
	createDoor(-13, 12, ORANGE, SOUTH);
	createDoor(-15, -8, CYAN, NORTH);

	//CREATES TROPHY
	createTrophy(-10.5, -14);
}

void World::createFloor()
{
	GameObject* floor = new GameObject();
	floor->addComponent(new FloorComponent());
	gameObjects.push_back(floor);
}

void World::createOuterWalls()
{
	GameObject* outerWalls1 = new GameObject();
	outerWalls1->addComponent(new WallComponent(-16, -16, 16, -16));
	outerWalls1->addComponent(new LineCollisionComponent(-16, -16, 16, -16));
	GameObject* outerWalls2 = new GameObject();
	outerWalls2->addComponent(new WallComponent(16, -16, 16, 16));
	outerWalls2->addComponent(new LineCollisionComponent(16, -16, 16, 16));
	GameObject* outerWalls3 = new GameObject();
	outerWalls3->addComponent(new WallComponent(16, 16, -16, 16));
	outerWalls3->addComponent(new LineCollisionComponent(16, 16, -16, 16));
	GameObject* outerWalls4 = new GameObject();
	outerWalls4->addComponent(new WallComponent(-16, 16, -16, -16));
	outerWalls4->addComponent(new LineCollisionComponent(-16, 16, -16, -16));
	gameObjects.push_back(outerWalls1);	
	gameObjects.push_back(outerWalls2);
	gameObjects.push_back(outerWalls3);
	gameObjects.push_back(outerWalls4);
}

void World::createDoor(float x, float z, Color color, Direction direction)
{
	GameObject* door = new GameObject();
	DoorComponent* doorComponent = new DoorComponent(x, z, color, direction);
	doorComponent->setGameObject(door);
	doorComponent->setRotationPoint();
	door->addComponent(doorComponent);

	int incrementX = 0;
	int incrementZ = 0;
	switch (direction) {
	case NORTH:
		incrementX = 2;
		break;
	case EAST:
		incrementZ = -2;
		break;
	case SOUTH:
		incrementX = -2;
		break;
	case WEST:
		incrementZ = 2;
		break;
	}
	door->addComponent(new LineCollisionComponent(x, z, x + incrementX, z + incrementZ));
	gameObjects.push_back(door);
}

void World::createHedge(float startX, float startZ, float endX, float endZ)
{
	GameObject* hedge = new GameObject();
	hedge->addComponent(new HedgeComponent(startX, startZ, endX, endZ));
	hedge->addComponent(new LineCollisionComponent(startX, startZ, endX, endZ));
	gameObjects.push_back(hedge);
}

void World::createKey(float x, float z, Color color)
{
	GameObject* key = new GameObject(x, 1.5f, z);
	ModelComponent* keyComponent = new ModelComponent("Models/key.obj", x, z, color);
	keyComponent->setGameObject(key);
	keyComponent->setRotationPoint();
	key->addComponent(keyComponent);
	gameObjects.push_back(key);
}

void World::createTrophy(float x, float z)
{
	GameObject* trophy = new GameObject(x, 1.5f, z);
	ModelComponent* keyComponent = new ModelComponent("Models/trophy.obj", x, z, ORANGE);
	keyComponent->setGameObject(trophy);
	keyComponent->setRotationPoint();
	trophy->addComponent(keyComponent);
	gameObjects.push_back(trophy);
}

