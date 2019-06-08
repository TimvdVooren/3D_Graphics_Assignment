#include "ModelComponent.h"
#include <string>

ModelComponent::ModelComponent(std::string fileName, float x, float z, ObjColor objectColor)
{
	model = ObjModel(fileName);
	this->x = x;
	this->z = z;
	this->objectColor = objectColor;
}

ModelComponent::~ModelComponent(){}

void ModelComponent::setColor()
{
	switch (objectColor) {
		case RED:
			glColor3f(1.0f, 0.0f, 0.0f);
			break;
		case GREEN:
			glColor3f(0.0f, 1.0f, 0.0f);
			break;
		case BLUE:
			glColor3f(0.0f, 0.0f, 1.0f);
			break;
		case PURPLE:
			glColor3f(1.0f, 0.0f, 1.0f);
			break;
		case ORANGE:
			glColor3f(1.0f, 1.0f, 0.0f);
			break;
		case YELLOW:
			glColor3f(0.0f, 1.0f, 1.0f);
			break;
	}
}

void ModelComponent::draw()
{
	glTranslatef(x, 1.5f, z);
	glScalef(0.0075f, 0.0075f, 0.0075f);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	setColor();
	model.draw();
}
