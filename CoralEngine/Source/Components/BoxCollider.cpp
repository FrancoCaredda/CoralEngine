#include "BoxCollider.h"
#include <Components/Transform.h>

BoxCollider::BoxCollider(AGameObject* owner) : m_Owner(owner)
{
	ShrinkToSize();
}

AGameObject* BoxCollider::GetOwner() const
{
	return m_Owner;
}

void BoxCollider::SetWidth(float width)
{
	m_Width = width;
}

void BoxCollider::SetHeight(float height)
{
	m_Height = height;
}

float BoxCollider::GetWidth() const
{
	return m_Width;
}

float BoxCollider::GetHeight() const
{
	return m_Height;
}

glm::vec2 BoxCollider::GetMin() const
{
	Transform* parentTransform = m_Owner->GetComponent<Transform>();
	return glm::vec2(parentTransform->GetPosition().x, parentTransform->GetPosition().y);
}

glm::vec2 BoxCollider::GetMax() const
{
	glm::vec2 min = GetMin();
	return glm::vec2(min.x + m_Width, min.y + m_Height);
}

void BoxCollider::ShrinkToSize()
{
	glm::vec2 size = m_Owner->GetTransform()->GetSize();
	m_Width = size.x;
	m_Height = size.y;
}

bool BoxCollider::HasCollision(const BoxCollider& other)
{
	glm::vec2 ownMin = GetMin();
	glm::vec2 ownMax = GetMax();
	glm::vec2 otherMin = other.GetMin();
	glm::vec2 otherMax = other.GetMax();

	if (ownMax.x < otherMin.x || ownMin.x > otherMax.x) return false;
	if (ownMax.y < otherMin.y || ownMin.y > otherMax.y) return false;

	return true;
}

Manifold BoxCollider::GetManifoldWith(const BoxCollider& other)
{
	Manifold collisionResult;
	collisionResult.A = m_Owner->GetComponent<PhysicsComponent>();
	collisionResult.B = other.m_Owner->GetComponent<PhysicsComponent>();

	// calculates the centre of the rect A
	glm::vec2 centreA = m_Owner->GetComponent<Transform>()->GetPosition();
	centreA.x += m_Width / 2;
	centreA.y += m_Height / 2;

	// calculates the centre of the rect B
	glm::vec2 centreB = other.m_Owner->GetComponent<Transform>()->GetPosition();
	centreB.x += other.m_Width / 2;
	centreB.y += other.m_Height / 2;

	glm::vec2 n = centreA - centreB;

	// calculating half of width 
	float extentA = (GetMax().x - GetMin().x) / 2;
	float extentB = (other.GetMax().x - other.GetMin().x) / 2;

	// calculating x overlapping
	float overlapX = (extentA + extentB) - abs(n.x);

	if (overlapX > 0)
	{
		// calculating half of height 
		float extentA = (GetMax().y - GetMin().y) / 2;
		float extentB = (other.GetMax().y - other.GetMin().y) / 2;

		// calculating y overlapping
		float overlapY = (extentA + extentB) - abs(n.y);

		if (overlapY > 0)
		{
			// determine on which of the axes the overlapping is smaller
			if (overlapX < overlapY)
			{
				if (n.x < 0)
					collisionResult.normal = glm::vec2(1, 0);
				else
					collisionResult.normal = glm::vec2(-1, 0);
				collisionResult.penetration = overlapX;
			}
			else
			{
				if (n.y < 0)
					collisionResult.normal = glm::vec2(0, 1);
				else
					collisionResult.normal = glm::vec2(0, -1);
				collisionResult.penetration = overlapY;
			}
		}
	}

	return collisionResult;
}
