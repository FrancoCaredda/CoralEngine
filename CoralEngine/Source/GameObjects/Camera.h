#ifndef CAMERA_H
#define CAMERA_H

#include "defines.h"
#include "GameObject.h"

class CORAL_API Camera : public AGameObject
{
public:
	Camera();

	virtual void Start() override { }
	virtual void Update(float deltaTime) override { }

	virtual ~Camera() { };
};

#endif // !CAMERA_H



