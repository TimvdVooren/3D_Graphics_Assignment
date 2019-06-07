#pragma once

#include <vector>
#include <string>

class Component;

class GameObject
{
	std::vector<Component*> components;

public:
	GameObject();
	~GameObject();

	void addComponent(Component* component);
	std::vector<Component*> getComponents();

	void update(float elapsedTime);
	void handleEvent(float elapsedTime);
	void draw();
};
