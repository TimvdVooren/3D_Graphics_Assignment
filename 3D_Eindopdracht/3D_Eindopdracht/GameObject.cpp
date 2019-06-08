#include "GameObject.h"
#include "Component.h"
#include "GL/freeglut.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::addComponent(Component * component)
{
	components.push_back(component);
}

std::vector<Component*> GameObject::getComponents()
{
	return components;
}

void GameObject::update(float elapsedTime)
{
	for (Component* c : components)
	{
		c->update(elapsedTime);
	}
}

void GameObject::handleEvent(float elapsedTime)
{
	for (Component* c : components)
	{
		c->handleEvent(elapsedTime);
	}
}

void GameObject::draw()
{
	for (Component* c : components)
	{
		glRotatef(rotationX, 1, 0, 0);
		glRotatef(rotationY, 0, 1, 0);
		glRotatef(rotationZ, 0, 0, 1);
		c->draw();
	}
}
