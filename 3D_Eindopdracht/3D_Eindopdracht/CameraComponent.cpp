#include "CameraComponent.h"
#include <iostream>

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::move(float distance, Direction direction)
{
	switch (direction) {
	case UP:
		camera.posY -= distance;
		break;
	case DOWN:
		camera.posY += distance;
		break;
	default:
		float distanceX = cosf((camera.rotY + direction) / 180 * M_PI) * distance;
		float distanceZ = sinf((camera.rotY + direction) / 180 * M_PI) * distance;

		if (gameObject->isCollidingNorth && distanceZ > 0) {
			std::cout << "Can't move north";
			distanceZ = 0;
		}
		if (gameObject->isCollidingEast && distanceX < 0) {
			std::cout << "Can't move east";
			distanceX = 0;
		}
		if (gameObject->isCollidingSouth && distanceZ < 0) {
			std::cout << "Can't move south";
			distanceZ = 0;
		}
		if (gameObject->isCollidingWest && distanceX > 0) {
			std::cout << "Can't move west";
			distanceX = 0;
		}

		camera.posX += distanceX;
		camera.posZ += distanceZ;
		break;
	}
}

void CameraComponent::rotate(float delta, Axis axis)
{
	switch (axis) {
	case X:
		camera.rotX += delta / 10.0f;
		break;
	case Y:
		camera.rotY += delta / 10.0f;
		break;
	case Z:
		break;
	}
}

Camera CameraComponent::getCamera()
{
	return camera;
}
