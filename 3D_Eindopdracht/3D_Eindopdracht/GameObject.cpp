#include "GameObject.h"
#include "Component.h"
#include "GL/freeglut.h"
#include "ObjColor.h"
#include "LineCollisionComponent.h"
#include "CircleCollisionComponent.h"

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
	component->setGameObject(this);
	components.push_back(component);
}

std::vector<Component*> GameObject::getComponents()
{
	return components;
}

void GameObject::update(float elapsedTime, float playerX, float playerZ, std::vector<ObjColor>* keys)
{
	for (Component* c : components)
	{
		c->update(elapsedTime, playerX, playerZ, keys);
	}
}

void GameObject::handleEvent(float elapsedTime, float playerX, float playerZ, std::vector<ObjColor>* keys)
{
	for (Component* c : components)
	{
		c->handleEvent(elapsedTime, playerX, playerZ, keys);
	}
}

void GameObject::draw()
{
	for (Component* c : components)
	{
		bool draw = true;

		if (LineCollisionComponent* lineComponent = dynamic_cast<LineCollisionComponent*> (c))
		{
			draw = debugging;
		}
		else if (CircleCollisionComponent* circleComponent = dynamic_cast<CircleCollisionComponent*> (c))
		{
			draw = debugging;
		}

		if (draw) {
			glTranslatef(position.x, position.y, position.z);
			glTranslatef(rotationPoint.x, rotationPoint.y, rotationPoint.z);
			glRotatef(rotationX, 1, 0, 0);
			glRotatef(rotationY, 0, 1, 0);
			glRotatef(rotationZ, 0, 0, 1);
			glTranslatef(-rotationPoint.x, -rotationPoint.y, -rotationPoint.z);
			c->draw();
			glTranslatef(-position.x, -position.y, -position.z);
		}
	}
}

