#include "ModelComponent.h"
#include <string>
#include <iostream>

ModelComponent::ModelComponent(std::string fileName, float x, float z, Color color)
{
	model = ObjModel(fileName);
	this->x = x;
	this->z = z;
	this->objColor = ObjColor(color);
	scale = 0.0075f;
}

ModelComponent::~ModelComponent(){}

void ModelComponent::draw()
{
	glScalef(scale, scale, scale);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	objColor.setColor();
	model.draw();
}

void ModelComponent::update(float elapsedTime)
{
	gameObject->rotationY += elapsedTime * speed;
}

void ModelComponent::setRotationPoint()
{
	::Vec3f center = model.getCenter();
	std::cout << center.x << " " << center.y << " " << center.z;
	::Vec3f scaledCenter = ::Vec3f(center.x * scale, center.y * scale, center.z * scale);
	gameObject->rotationPoint = scaledCenter;
}
