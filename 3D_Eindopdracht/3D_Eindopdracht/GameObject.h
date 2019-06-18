#pragma once

#include <vector>
#include <string>
#include "Vec.h"
#include "ObjColor.h"

class Component;

class GameObject
{
	std::vector<Component*> components;

public:
	float rotationX = 0;
	float rotationY = 0;
	float rotationZ = 0;
	::Vec3f position;
	::Vec3f rotationPoint; 
	bool isCollidingNorth = false;
	bool isCollidingEast = false;
	bool isCollidingSouth = false;
	bool isCollidingWest = false;

	bool debugging = false;

	GameObject();
	GameObject(float x, float y, float z);
	~GameObject();

	void addComponent(Component* component);
	std::vector<Component*> getComponents();

	void update(float elapsedTime, float playerX, float playerZ, std::vector<ObjColor>* keys);
	void handleEvent(float elapsedTime, float playerX, float playerZ, std::vector<ObjColor>* keys);
	void draw();
};
