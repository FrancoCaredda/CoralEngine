#include "Transform.h"

#include "glm/gtx/transform.hpp"

Transform::Transform(AGameObject* owner)
{
	m_Owner = owner;

	m_Transform = glm::mat4(1.0f);
}

void Transform::Translate(const glm::vec3& position)
{
	m_Position += position;

	glm::vec3 correctedPosition = (position) / (m_Size / glm::vec3(50, 50, 1));

	m_Transform = glm::translate(m_Transform, correctedPosition);
}

void Transform::Rotate(const glm::vec3& rotation, float angle)
{
	m_Rotation = angle;

	m_Transform = glm::rotate(m_Transform, glm::radians(angle), rotation);
}

void Transform::Scale(const glm::vec3& size)
{
	m_Size.x *= size.x;
	m_Size.y *= size.y;
	m_Size.z *= size.z;

	m_Transform = glm::scale(m_Transform, size);
}
