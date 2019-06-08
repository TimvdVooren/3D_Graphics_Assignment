#include "ModelComponent.h"
#include <string>

ModelComponent::ModelComponent(std::string fileName, float x, float z, Color color)
{
	model = ObjModel(fileName);
	this->x = x;
	this->z = z;
	this->objColor = ObjColor(color);
}

ModelComponent::~ModelComponent(){}

void ModelComponent::draw()
{
	glTranslatef(x, 1.5f, z);
	glScalef(0.0075f, 0.0075f, 0.0075f);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	objColor.setColor();
	model.draw();
}
