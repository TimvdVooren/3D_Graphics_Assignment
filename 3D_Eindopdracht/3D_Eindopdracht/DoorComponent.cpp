#include "DoorComponent.h"
#include "Texture.h"
#include <math.h> 
#include <iostream> 
#include <algorithm>
#include <vector> 
#include "LineCollisionComponent.h"

DoorComponent::DoorComponent(float x, float z, Color color, Direction facingDirection)
{
	this->x = x;
	this->z = z;
	this->objColor = ObjColor(color);
	this->facingDirection = facingDirection;
	doorTexture = Texture("Textures/door_texture.jpg");
}

DoorComponent::~DoorComponent(){}

void DoorComponent::draw()
{
	glEnable(GL_TEXTURE_2D);
	doorTexture.bind();

	objColor.setColor();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(x, 0, z);
	glTexCoord2f(1, 0); glVertex3f(x + 2, 0, z);
	glTexCoord2f(1, 1); glVertex3f(x+2, 4, z);
	glTexCoord2f(0, 1); glVertex3f(x, 4, z);
	glEnd();
}

void DoorComponent::update(float elapsedTime, float playerX, float playerZ, std::vector<ObjColor>* keys)
{
	if (gameObject->rotationY < facingDirection && open)
	{
		gameObject->rotationY += elapsedTime * speed;
	}
	else if (gameObject->rotationY > facingDirection - 90 && !open) {
		gameObject->rotationY -= elapsedTime * speed;
	}
}

void DoorComponent::handleEvent(float elapsedTime, float playerX, float playerZ, std::vector<ObjColor>* keys)
{
	float xDifference = x + playerX;
	float zDifference = z + playerZ;
	float distanceToPlayer = sqrt(pow(xDifference, 2) + pow(zDifference, 2)); 
	bool keyFound = std::find(keys->begin(), keys->end(), objColor) != keys->end();

	if (distanceToPlayer <= 1.5f && keyFound && !open) {
		open = !open;
		for (auto c : gameObject->getComponents()) {
			if (LineCollisionComponent* line = dynamic_cast<LineCollisionComponent*> (c)) {
				delete line;
			}
		}
	}
}

void DoorComponent::setRotationPoint()
{
	gameObject->rotationPoint = ::Vec3f(x, 0, z);
	gameObject->rotationY = facingDirection - 90;
}
