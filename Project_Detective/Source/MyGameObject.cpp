#include "MyGameObject.h"

#include "Components/Sprite.h"
#include "Components/Transform.h"
#include "Components/BoxCollider.h"
#include "Components/PhysicsComponent.h"

#include "Core/Renderer.h"

#include "Core/Asset.h"
#include "Core/AssetManager.h"

void MyGameObject::Start()
{
	Sprite* sprite = AddComponent<Sprite>();
	sprite->SetTexture(AssetManager::GetAssetHandle("smile"));

	BoxCollider* collider = AddComponent<BoxCollider>();
	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
}

void MyGameObject::Update(float deltaTime)
{
	//GetComponent<Transform>()->Translate(glm::vec3(m_Speed * deltaTime, 0.0f, 0.0f));
	//glm::vec3 position = m_Transform->GetPosition();
	PhysicsComponent* physics = GetComponent<PhysicsComponent>();
	physics->Update(deltaTime);

	if (GetComponent<Transform>()->GetPosition().x <= 0)
		physics->SetVelocity(abs(physics->GetVelocity().x), physics->GetVelocity().y);
	if (GetComponent<Transform>()->GetPosition().x >= 600 - GetComponent<BoxCollider>()->GetWidth())
		physics->SetVelocity(abs(physics->GetVelocity().x) * -1, physics->GetVelocity().y);

	if (GetComponent<Transform>()->GetPosition().y <= 0)
		physics->SetVelocity(physics->GetVelocity().x, abs(physics->GetVelocity().y));
	if (GetComponent<Transform>()->GetPosition().y >= 480 - GetComponent<BoxCollider>()->GetHeight())
		physics->SetVelocity(physics->GetVelocity().x, abs(physics->GetVelocity().y)*-1);

}

MyGameObject::~MyGameObject()
{
}
