#pragma once

#include "Component.h"
#include "ObjModel.h"
#include "ObjColor.h"

class ModelComponent : virtual public Component
{
	ObjModel model;
	float x;
	float z;
	ObjColor objColor;
	int speed = 50;
	float scale = 1.0f;
	bool pickedUp = false;
	bool isTrophy = false;

public:
	ModelComponent(std::string fileName, float x, float z, Color color);
	~ModelComponent();

	void draw() override;
	void update(float elapsedTime, float playerX, float playerZ, std::vector<ObjColor>* keys) override;
	void setRotationPoint();
};
