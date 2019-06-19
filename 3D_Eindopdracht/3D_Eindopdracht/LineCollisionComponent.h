#pragma once
#include "CollisionComponent.h"
#include <vector>
#include "Vec.h"

struct Hitline
{
	::Vec2f point1;
	::Vec2f point2;
};

class LineCollisionComponent : public CollisionComponent {
public:
	Hitline hitline;

	LineCollisionComponent(float startX, float startZ, float endX, float endZ);
	~LineCollisionComponent();

	void draw() override;
};