#pragma once
#include "GameObject.h"

class Component
{
protected:
	GameObject* gameObject;
public:
	explicit Component();
	virtual ~Component();

	virtual void draw() {};
	virtual void update(float elapsedTime) {};
	virtual void handleEvent(float elapsedTime) {};
	virtual inline void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
};