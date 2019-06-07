#pragma once

#include "Component.h"
#include "Texture.h"

class DoorComponent : virtual public Component
{
	Texture doorTexture;
	float x;
	float z;
	bool open = false;
	int speed = 100;

public:
	DoorComponent(float x, float z);
	~DoorComponent();

	void draw();
	void update(float elapsedTime);
	void handleEvent(float elapsedTime);
};
