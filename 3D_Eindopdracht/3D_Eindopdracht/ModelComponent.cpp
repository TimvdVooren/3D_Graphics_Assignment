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
	if (!pickedUp) {
		glScalef(scale, scale, scale);
		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		objColor.setColor();
		model.draw();
	}
}

void ModelComponent::update(float elapsedTime, float playerX, float playerZ, std::vector<ObjColor>* keys)
{
	gameObject->rotationY += elapsedTime * speed;

	float xDifference = x + playerX;
	float zDifference = z + playerZ + 1.5f;
	float distanceToPlayer = sqrt(pow(xDifference, 2) + pow(zDifference, 2));
	if (distanceToPlayer <= 1.5f && !pickedUp) {
		pickedUp = true;
		keys->push_back(objColor);
	}
}

void ModelComponent::setRotationPoint()
{
	::Vec3f center = model.getCenter();
	std::cout << center.x << " " << center.y << " " << center.z;
	::Vec3f scaledCenter = ::Vec3f(center.x * scale, center.y * scale, center.z * scale);
	gameObject->rotationPoint = scaledCenter;
}
