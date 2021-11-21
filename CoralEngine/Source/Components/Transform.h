#ifndef TRANSFORM_H
#define TRANSFORM_H


#include "defines.h"

#include "GameObjects/GameObject.h"

#include "glm/glm.hpp"

class CORAL_API Transform
{
public:
	Transform(AGameObject* owner);

	void Translate(const glm::vec3& position);
	void Rotate(const glm::vec3& rotation, float angle);
	void Scale(const glm::vec3& size);

	inline glm::mat4 GetTransform() { return m_Transform; }
	inline glm::vec3 GetPosition() { return m_Position; }

	inline AGameObject* GetOwner() { return m_Owner; }
private:
	glm::vec3 m_Position;
	glm::vec3 m_Size;

	float m_Rotation;

	glm::mat4 m_Transform;

	AGameObject* m_Owner;
};


#endif // !TRANSFORM_H