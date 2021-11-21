#include "GameObject.h"

AGameObject::AGameObject(const std::string& name)
	: m_Name(name)
{
}

AGameObject::~AGameObject()
{
	for (auto i = m_Components.begin();
		i != m_Components.end(); i++)
	{
		delete i->second;
	}
}
