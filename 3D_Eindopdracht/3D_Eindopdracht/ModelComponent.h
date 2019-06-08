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

public:
	ModelComponent(std::string fileName, float x, float z, Color color);
	~ModelComponent();

	void draw();
	void update(float elapsedTime);
	void setRotationPoint();
};
