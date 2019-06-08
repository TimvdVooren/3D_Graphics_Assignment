#include "GameObject.h"
#include "Component.h"
#include "GL/freeglut.h"

GameObject::GameObject(float x, float y, float z)
{
	position = ::Vec3f(x, y, z);
	rotationPoint = ::Vec3f(0, 0, 0);
}

GameObject::GameObject()
{
	position = ::Vec3f(0, 0, 0);
	rotationPoint = ::Vec3f(0, 0, 0);
}

GameObject::~GameObject(){}

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
		glTranslatef(position.x, position.y, position.z);
		glTranslatef(rotationPoint.x, rotationPoint.y, rotationPoint.z);
		glRotatef(rotationX, 1, 0, 0);
		glRotatef(rotationY, 0, 1, 0);
		glRotatef(rotationZ, 0, 0, 1);
		glTranslatef(-rotationPoint.x, -rotationPoint.y, -rotationPoint.z);
		c->draw();
	}
}
