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

public:
	ModelComponent(std::string fileName, float x, float z, Color color);
	~ModelComponent();

	void draw();
};
