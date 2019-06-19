#pragma once

#include "Component.h"
#include "Texture.h"

class FloorComponent : virtual public Component
{
	Texture floorTexture;

public:
	FloorComponent();
	~FloorComponent();

	void draw() override;
};
