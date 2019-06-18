#include "CollisionManager.h"
#include "CircleCollisionComponent.h"
#include "LineCollisionComponent.h"
#include <iostream>

bool CollisionManager::isPointOnLine(float px, float pz, Hitline hitline)
{
	float x1 = hitline.point1.x,
		x2 = hitline.point2.x,
		z1 = hitline.point1.y,
		z2 = hitline.point2.y;

	float d1 = calculateDistance(px, pz, x1, z1),
		d2 = calculateDistance(px, pz, x2, z2);

	float lineLength = calculateDistance(x1, z1, x2, z2);

	float buffer = 0.2f;

	return d1 + d2 >= lineLength - buffer && d1 + d2 <= lineLength + buffer;
}

float CollisionManager::calculateDistance(float x1, float z1, float x2, float z2)
{
	return sqrt(pow((x1 - x2), 2) + pow((z1 - z2), 2));
}

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::isColliding(GameObject * player, GameObject * object)
{
	LineCollisionComponent* objectLine = nullptr;
	for (auto c : object->getComponents()) {
		objectLine = dynamic_cast<LineCollisionComponent*>(c);
	}

	if (objectLine == nullptr)
		return;

	CircleCollisionComponent* playerCircle = nullptr;
	for (auto c : player->getComponents()) {
		playerCircle = dynamic_cast<CircleCollisionComponent*>(c);
	}

	float playerX = playerCircle->circle.x;
	float playerZ = playerCircle->circle.z;
	float minPlayerX = playerX - playerCircle->circle.radius;
	float maxPlayerX = playerX + playerCircle->circle.radius;
	float minPlayerZ = playerZ - playerCircle->circle.radius;
	float maxPlayerZ = playerZ + playerCircle->circle.radius;
	Hitline hitline = objectLine->hitline;

	if (isPointOnLine(maxPlayerX, playerZ, hitline)) {
		player->isCollidingNorth = true;
		std::cout << "COLLISION N\n";
	}
	else {
		player->isCollidingNorth = false;
	}

	if (isPointOnLine(playerX, maxPlayerZ, hitline)) {
		player->isCollidingEast = true;
		std::cout << "COLLISION E\n";
	}
	else {
		player->isCollidingEast = false;
	}

	if (isPointOnLine(minPlayerX, playerZ, hitline)) {
		player->isCollidingSouth = true;
		std::cout << "COLLISION S\n";
	}
	else {
		player->isCollidingSouth = false;
	}

	if (isPointOnLine(playerX, minPlayerZ, hitline)) {
		player->isCollidingWest = true;
		std::cout << "COLLISION W\n";
	}
	else {
		player->isCollidingWest = false;
	}
	
}
