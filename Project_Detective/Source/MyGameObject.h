#pragma once

#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"

#include "Components/Sprite.h"
#include "Components/Transform.h"

class MyGameObject : public AGameObject
{
public:
	MyGameObject(const std::string& name)
		: AGameObject(name) { }

	virtual void Start() override;
	virtual void Update(float deltaTime) override;

	virtual ~MyGameObject() override;
private:
	Sprite* m_Sprite;
};

