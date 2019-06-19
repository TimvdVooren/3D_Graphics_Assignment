#pragma once
#include "CollisionComponent.h"
#include <vector>

struct Circle
{
	float x, z, radius;
};

class CircleCollisionComponent : public CollisionComponent {
public:
	Circle circle;

	CircleCollisionComponent(float x, float z, float radius);
	~CircleCollisionComponent();

	void update(float elapsedTime, float playerX, float playerZ, std::vector<ObjColor>* keys) override;
	void draw() override;
};