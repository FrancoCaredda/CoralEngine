#include "GameObject.h"
#include <Components/Transform.h>

AGameObject::AGameObject(const std::string& name)
	: m_Name(name)
{
	Transform * pos = AddComponent<Transform>();
}

AGameObject::~AGameObject()
{
	for (auto i = m_Components.begin();
		i != m_Components.end(); i++)
	{
		delete i->second;
	}
}
