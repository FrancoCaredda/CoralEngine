#ifndef BOX_COLLIDER
#define BOX_COLLIDER

#include <glm/glm.hpp>
#include <GameObjects/GameObject.h>
#include <defines.h>

class CORAL_API BoxCollider
{
private:
	AGameObject *m_Owner;

	float m_Width, m_Height;

public:
	BoxCollider(AGameObject* owner);

	void SetWidth(float width);
	void SetHeight(float height);

	// returns bottom left position
	glm::vec2 GetMin();
	// returns upper right position
	glm::vec2 GetMax();

	bool HasCollision(BoxCollider* other);
};

#endif // !BOX_COLLIDER