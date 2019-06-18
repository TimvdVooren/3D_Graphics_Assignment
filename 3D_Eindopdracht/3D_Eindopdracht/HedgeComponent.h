#pragma once

#include "Component.h"
#include "Texture.h"

class HedgeComponent : virtual public Component
{
	Texture hedgeTexture;
	float startX;
	float startZ;
	float endX;
	float endZ;

public:
	HedgeComponent(float startX, float startZ, float endX, float endZ);
	~HedgeComponent();

	void draw() override;
};
