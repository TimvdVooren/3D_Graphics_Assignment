#pragma once

#include "GL/freeglut.h"

enum Color { NONE, RED, GREEN, BLUE, PURPLE, ORANGE, YELLOW };

class ObjColor {
	Color color;

public:
	ObjColor(Color color);
	ObjColor();
	~ObjColor();

	void setColor();
};