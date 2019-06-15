#pragma once

#include "Component.h"
#include "Texture.h"
#include "ObjColor.h"
#include "Direction.h"
#include "Vec.h"

class DoorComponent : virtual public Component
{
	Texture doorTexture;
	float x;
	float z;
	bool open = false;
	int speed = 100;
	ObjColor objColor;
	Direction facingDirection;

public:
	DoorComponent(float x, float z, Color color, Direction facingDirection);
	~DoorComponent();

	void draw();
	void update(float elapsedTime);
	void handleEvent(float elapsedTime);
	void setRotationPoint();
};
