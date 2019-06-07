#include "GameObject.h"
#include "Component.h"

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
		c->draw();
	}
}
