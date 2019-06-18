#pragma once
#include "Component.h"
#include <vector>
#include "Vec.h"

class CollisionComponent: virtual public Component {
public:
	CollisionComponent();
	~CollisionComponent();

	virtual void drawHitbox() {};
};