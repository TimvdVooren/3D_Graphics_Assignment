#include "ObjColor.h"

ObjColor::ObjColor(Color color)
{
	this->color = color;
}

ObjColor::ObjColor(){}

ObjColor::~ObjColor(){}

void ObjColor::setColor()
{
	switch (color) {
		case NONE:
			glColor3f(1.0f, 1.0f, 1.0f);
			break;
		case RED:
			glColor3f(1.0f, 0.0f, 0.0f);
			break;
		case GREEN:
			glColor3f(0.0f, 1.0f, 0.0f);
			break;
		case BLUE:
			glColor3f(0.0f, 0.0f, 1.0f);
			break;
		case PURPLE:
			glColor3f(1.0f, 0.0f, 1.0f);
			break;
		case ORANGE:
			glColor3f(1.0f, 1.0f, 0.0f);
			break;
		case CYAN:
			glColor3f(0.0f, 1.0f, 1.0f);
			break;
	}
}
