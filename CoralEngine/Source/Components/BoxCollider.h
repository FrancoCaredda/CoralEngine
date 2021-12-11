#ifndef BOX_COLLIDER
#define BOX_COLLIDER

#include <glm/glm.hpp>
#include <GameObjects/GameObject.h>
#include <defines.h>
#include <Components/PhysicsComponent.h>

class CORAL_API Manifold
{
public:
	PhysicsComponent* A;
	PhysicsComponent* B;

	float penetration;
	glm::vec2 normal;
};

class CORAL_API BoxCollider
{
private:
	AGameObject *m_Owner;

	float m_Width, m_Height;

public:
	BoxCollider(AGameObject* owner);
	AGameObject* GetOwner() const;

	void SetWidth(float width);
	void SetHeight(float height);

	float GetWidth() const;
	float GetHeight() const;

	// returns bottom left position
	glm::vec2 GetMin() const;
	// returns upper right position
	glm::vec2 GetMax() const;

	void ShrinkToSize();

	bool HasCollision(const BoxCollider& other);
	Manifold GetManifoldWith(const BoxCollider& other);
};

#endif // !BOX_COLLIDER