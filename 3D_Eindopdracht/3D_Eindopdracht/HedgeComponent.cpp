#include "HedgeComponent.h"

HedgeComponent::HedgeComponent(float startX, float startZ, float endX, float endZ)
{
	this->startX = startX;
	this->startZ = startZ;
	this->endX = endX;
	this->endZ = endZ;
	hedgeTexture = Texture("Textures/hedge_texture.jpg");
}

HedgeComponent::~HedgeComponent(){}

void HedgeComponent::draw()
{
	glEnable(GL_TEXTURE_2D);
	hedgeTexture.bind();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(startX, 0, startZ);
	glTexCoord2f(1, 0); glVertex3f(endX, 0, endZ);
	glTexCoord2f(1, 1); glVertex3f(endX, 4, endZ);
	glTexCoord2f(0, 1); glVertex3f(startX, 4, startZ);
	glEnd();
}
