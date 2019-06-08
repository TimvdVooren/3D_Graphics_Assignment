#pragma once

#include <vector>
#include <string>
#include "Vec.h"

class Component;

class GameObject
{
	std::vector<Component*> components;

public:
	float rotationX = 0;
	float rotationY = 0;
	float rotationZ = 0;
	::Vec3f rotationPoint;

	GameObject();
	~GameObject();

	void addComponent(Component* component);
	std::vector<Component*> getComponents();

	void update(float elapsedTime);
	void handleEvent(float elapsedTime);
	void draw();
};
