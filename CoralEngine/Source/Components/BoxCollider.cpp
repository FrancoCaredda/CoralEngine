#include "BoxCollider.h"
#include <Components/Transform.h>

BoxCollider::BoxCollider(AGameObject* owner) : m_Owner(owner)
{}

void BoxCollider::SetWidth(float width)
{
	m_Width = width;
}

void BoxCollider::SetHeight(float height)
{
	m_Height = height;
}

glm::vec2 BoxCollider::GetMin()
{
	Transform* parentTransform = m_Owner->GetComponent<Transform>();
	return glm::vec2(parentTransform->GetPosition().x, parentTransform->GetPosition().y);
}

glm::vec2 BoxCollider::GetMax()
{
	glm::vec2 min = GetMin();
	return glm::vec2(min.x + m_Width, min.y + m_Height);
}

bool BoxCollider::HasCollision(BoxCollider* other)
{
	glm::vec2 ownMin = GetMin();
	glm::vec2 ownMax = GetMax();
	glm::vec2 otherMin = other->GetMin();
	glm::vec2 otherMax = other->GetMax();

	if (ownMax.x < otherMin.x || ownMin.x > otherMax.x) return false;
	if (ownMax.y < otherMin.y || ownMin.y > otherMax.y) return false;

	return true;
}
