#include "LineCollisionComponent.h"

LineCollisionComponent::LineCollisionComponent(float startX, float startZ, float endX, float endZ)
{
	hitline.point1 = ::Vec2f(startX, startZ);
	hitline.point2 = ::Vec2f(endX, endZ);
}

LineCollisionComponent::~LineCollisionComponent(){}

void LineCollisionComponent::draw()
{
	glLineWidth(2.5f);

	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(hitline.point1.x, 4.1f, hitline.point1.y);
	glVertex3f(hitline.point2.x, 4.1f, hitline.point2.y);
	glEnd();

	glLineWidth(1.0f);
}
