#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::move(float distance, Direction direction)
{
	switch (direction) {
	case NORTH:
		camera.posX += cosf((camera.rotY + NORTH) / 180 * M_PI) * distance;
		camera.posZ += sinf((camera.rotY + NORTH) / 180 * M_PI) * distance;
		break;
	case EAST:
		camera.posX += cosf((camera.rotY + EAST) / 180 * M_PI) * distance;
		camera.posZ += sinf((camera.rotY + EAST) / 180 * M_PI) * distance;
		break;
	case SOUTH:
		camera.posX += cosf((camera.rotY + SOUTH) / 180 * M_PI) * distance;
		camera.posZ += sinf((camera.rotY + SOUTH) / 180 * M_PI) * distance;
		break;
	case WEST:
		camera.posX += cosf((camera.rotY + WEST) / 180 * M_PI) * distance;
		camera.posZ += sinf((camera.rotY + WEST) / 180 * M_PI) * distance;
		break;
	case UP:
		camera.posY -= distance;
		break;
	case DOWN:
		camera.posY += distance;
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
