#include "DoorComponent.h"
#include "Texture.h"

DoorComponent::DoorComponent(float x, float z)
{
	this->x = x;
	this->z = z;
	doorTexture = Texture("Textures/door_texture.jpg");
}

DoorComponent::~DoorComponent(){}

void DoorComponent::draw()
{
	glEnable(GL_TEXTURE_2D);
	doorTexture.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(x, 0, z);
	glTexCoord2f(1, 0); glVertex3f(x+2, 0, z);
	glTexCoord2f(1, 1); glVertex3f(x+2, 4, z);
	glTexCoord2f(0, 1); glVertex3f(x, 4, z);
	glEnd();
}

void DoorComponent::update(float elapsedTime)
{
	if (gameObject->rotationY < 90.0f && open)
	{
		gameObject->rotationY += elapsedTime * speed;
	}
	else if (gameObject->rotationY > 0.0f && !open) {
		gameObject->rotationY -= elapsedTime * speed;
	}
}

void DoorComponent::handleEvent(float elapsedTime)
{
	open = !open;
}
