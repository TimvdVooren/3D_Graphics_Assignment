#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

class World
{
	int width;
	int height;

	float deltaTime;
	float lastFrameTime;
	bool keys[255];
	bool justMovedMouse = false;

public:
	World(int, int);
	~World();

	void idle(void);
	void display();
	void reshape(int, int);
	void move(float, float);
	void keyboard(unsigned char, int, int);
	void keyboardUp(unsigned char, int, int);
	void mousePassiveMotion(int, int);
	void mouseClick(int, int, int, int);
	static World* getWorld();

	void spawnCube();
};