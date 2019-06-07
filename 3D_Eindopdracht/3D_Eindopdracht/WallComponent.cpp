#include "WallComponent.h"
#include "Texture.h"

WallComponent::WallComponent(float startX, float startZ, float endX, float endZ)
{
	this->startX = startX;
	this->startZ = startZ;
	this->endX = endX;
	this->endZ = endZ;
	wallTexture = Texture("Textures/wall_texture.jpg");
}

WallComponent::~WallComponent(){}

void WallComponent::draw()
{
	glEnable(GL_TEXTURE_2D);
	wallTexture.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(startX, 0, startZ);
	glTexCoord2f(5, 0); glVertex3f(endX, 0, endZ);
	glTexCoord2f(5, 1); glVertex3f(endX, 5, endZ);
	glTexCoord2f(0, 1); glVertex3f(startX, 5, startZ);
	glEnd();
}
