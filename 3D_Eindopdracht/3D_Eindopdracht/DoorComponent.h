#pragma once

#include "Component.h"
#include "Texture.h"
#include "ObjColor.h"

class DoorComponent : virtual public Component
{
	Texture doorTexture;
	float x;
	float z;
	bool open = false;
	int speed = 100;
	ObjColor objColor;

public:
	DoorComponent(float x, float z, Color color);
	~DoorComponent();

	void draw();
	void update(float elapsedTime);
	void handleEvent(float elapsedTime);
};
