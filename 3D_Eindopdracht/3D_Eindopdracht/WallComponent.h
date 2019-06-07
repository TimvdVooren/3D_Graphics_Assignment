#pragma once

#include "Component.h"
#include "Texture.h"
#include <tuple>

class WallComponent : virtual public Component
{
	Texture wallTexture;
	float startX;
	float startZ;
	float endX;
	float endZ;

public:
	WallComponent(float startX, float startZ, float endX, float endZ);
	~WallComponent();

	void draw();
};
