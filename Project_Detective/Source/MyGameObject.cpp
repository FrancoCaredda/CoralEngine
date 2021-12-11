#include "MyGameObject.h"

#include "Core/AssetManager.h"

void MyGameObject::Start()
{
	m_Sprite = AddComponent<Sprite>();
	m_Transform = AddComponent<Transform>();

	//m_Sprite->SetTexture(AssetManager::GetAssetHandle("smiling-face"));
	m_Sprite->SetColor({ 1.0, 0.0, 0.0, 1.0 });
}

void MyGameObject::Update(float deltaTime)
{
	GetComponent<Transform>()->Rotate(glm::vec3(0.0f, 0.0f, 1.0f), 2);
}

MyGameObject::~MyGameObject()
{
}
