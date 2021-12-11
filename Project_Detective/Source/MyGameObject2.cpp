#include "MyGameObject2.h"

#include "Components/Sprite.h"
#include "Components/Transform.h"
#include "Core/AssetManager.h"

void MyGameObject2::Start()
{
	Sprite* sprite = AddComponent<Sprite>();
	sprite->SetTexture(AssetManager::GetAssetHandle("smile"));

	sprite->SetColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
}

void MyGameObject2::Update(float deltaTime)
{
}
