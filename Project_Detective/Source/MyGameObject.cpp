#include "MyGameObject.h"

void MyGameObject::Start()
{
	m_Sprite = AddComponent<Sprite>();
	m_Transform = AddComponent<Transform>();

//	sprite->SetColor(glm::vec4(1.0f, 0.498f, 0.313f, 1.0f));


	m_Transform->Translate(glm::vec3(600 / 2 - 150, 480 / 2 - 150, 0));
	m_Transform->Scale(glm::vec3(2, 2, 0));
	m_Speed = 20;
}

void MyGameObject::Update(float deltaTime)
{
	m_Sprite->SetColor(glm::vec4(glm::sin(m_Speed * deltaTime), glm::cos(m_Speed * deltaTime), glm::sin(m_Speed * deltaTime), 1.0f));
}

MyGameObject::~MyGameObject()
{
	//delete m_Program;
}
