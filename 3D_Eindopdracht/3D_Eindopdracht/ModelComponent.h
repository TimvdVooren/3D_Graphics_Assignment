#pragma once

#include "Component.h"
#include "ObjModel.h"
#include "ObjColor.h"

class ModelComponent : virtual public Component
{
	ObjModel model;
	float x;
	float z;
	ObjColor objectColor;

public:
	ModelComponent(std::string fileName, float x, float z, ObjColor objectColor);
	~ModelComponent();

	void setColor();
	void draw();
};
