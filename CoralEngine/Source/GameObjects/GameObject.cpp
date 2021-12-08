#include "GameObject.h"
#include <Components/Transform.h>

AGameObject::AGameObject(const std::string& name)
	: m_Name(name)
{
	m_Transform = AddComponent<Transform>();
}

Transform* AGameObject::GetTransform() const
{
	return m_Transform;
}

std::string AGameObject::GetName() const
{
	return m_Name;
}

AGameObject::~AGameObject()
{
	for (auto i = m_Components.begin();
		i != m_Components.end(); i++)
	{
		delete i->second;
	}
}
