#pragma once
#include "GameObject.h"
#include "LineCollisionComponent.h"

class CollisionManager
{
	bool isPointOnLine(float px, float pz, Hitline hitline);
	float calculateDistance(float x1, float z1, float x2, float z2);
public:
	CollisionManager();
	~CollisionManager();

	void isColliding(GameObject *player, GameObject *object);
};