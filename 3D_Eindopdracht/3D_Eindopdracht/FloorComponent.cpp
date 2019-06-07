#include "FloorComponent.h"

FloorComponent::FloorComponent()
{
	floorTexture = Texture("Textures/grass_texture.jpg");
}

FloorComponent::~FloorComponent()
{
}

void FloorComponent::draw()
{
	glEnable(GL_TEXTURE_2D);
	floorTexture.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(-10, 0, -10);
	glTexCoord2f(1, 0); glVertex3f(10, 0, -10);
	glTexCoord2f(1, 1); glVertex3f(10, 0, 10);
	glTexCoord2f(0, 1); glVertex3f(-10, 0, 10);
	glEnd();
}
