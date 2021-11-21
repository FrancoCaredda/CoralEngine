#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "defines.h"

#include <string>
#include <typeinfo>
#include <unordered_map>

class CORAL_API AGameObject
{
public:
	AGameObject(const std::string& name);

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;

	template<typename T>
	T* AddComponent();

	template<typename T>
	bool HasComponent();

	template<typename T>
	T* GetComponent();

	virtual ~AGameObject();
private:
	std::string m_Name;
	std::unordered_map<std::string, void*> m_Components;
};

template<typename T>
inline T* AGameObject::AddComponent()
{
	std::string key = typeid(T).name();

	if (m_Components.find(key) == m_Components.end())
		m_Components[key] = new T(this);

	return (T*)m_Components[key];
}

template<typename T>
inline bool AGameObject::HasComponent()
{
	std::string key = typeid(T).name();

	if (m_Components.find(key) != m_Components.end())
		return true;

	return false;
}

template<typename T>
inline T* AGameObject::GetComponent()
{
	std::string key = typeid(T).name();

	if (m_Components.find(key) != m_Components.end())
		return (T*)m_Components[key];

	return nullptr;
}

#endif // !GAME_OBJECT


