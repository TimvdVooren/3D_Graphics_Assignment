#pragma once
#include "GameObject.h"
#include "ObjColor.h"
#include <vector>

class Component
{
protected:
	GameObject* gameObject;
public:
	explicit Component();
	virtual ~Component();

	virtual void draw() {};
	virtual void update(float elapsedTime, float playerX, float playerZ, std::vector<ObjColor>* keys) {};
	virtual void handleEvent(float elapsedTime, float playerX, float playerZ, std::vector<ObjColor>* keys) {};
	virtual inline void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
};