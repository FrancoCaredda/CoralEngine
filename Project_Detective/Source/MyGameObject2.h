#pragma once

#include "GameObjects/GameObject.h"

class MyGameObject2	: public AGameObject
{
public:
	MyGameObject2(const std::string& name)
		: AGameObject(name) { }

	virtual void Start() override;
	virtual void Update(float deltaTime) override;

	virtual ~MyGameObject2() { }
};

