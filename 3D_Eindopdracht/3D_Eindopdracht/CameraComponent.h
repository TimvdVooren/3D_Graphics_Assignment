#pragma once

#include "Component.h"
#include "Direction.h"

#define _USE_MATH_DEFINES
#include <math.h>

struct Camera
{
	float posX = -14;
	float posY = -3;
	float posZ = -14;
	float rotX = 10;
	float rotY = 0;
};

class CameraComponent : virtual public Component
{
	Camera camera;
public:
	CameraComponent();
	~CameraComponent();

	void move(float distance, Direction direction);
	void rotate(float delta, Axis axis);

	Camera getCamera();
};
