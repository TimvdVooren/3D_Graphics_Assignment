#include "CircleCollisionComponent.h"

CircleCollisionComponent::CircleCollisionComponent(float x, float z, float radius)
{
	circle.x = -x;
	circle.z = -z;
	circle.radius = radius;
}

CircleCollisionComponent::~CircleCollisionComponent(){}

void CircleCollisionComponent::update(float elapsedTime, float playerX, float playerZ, std::vector<ObjColor>* keys)
{
	circle.x = -playerX;
	circle.z = -playerZ;
}

void CircleCollisionComponent::draw()
{
	glColor3f(0, 1, 0);
	glLineWidth(2.5f);

	glBegin(GL_LINE_LOOP);
	glVertex3f(circle.x + circle.radius, 2.0f, circle.z);
	glVertex3f(circle.x, 2.0f, circle.z - circle.radius);
	glVertex3f(circle.x - circle.radius, 2.0f, circle.z);
	glVertex3f(circle.x, 2.0f, circle.z + circle.radius);
	glEnd();

	glLineWidth(1.0f);
}
