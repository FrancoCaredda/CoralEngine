#include "GameWindow.h"

#include "Core/Renderer.h"

#include <iostream>
#include <Components/BoxCollider.h>

GameWindow::GameWindow(const std::string& title, int width, int height, const CoralMonitor& monitor)
	: AWindow(title, width, height, monitor)
{
}

void GameWindow::Start()
{
	m_Object = new MyGameObject("Bob");
	m_Object->Start();
	m_Object->SetSpeed(0.005);

	m_Object2 = new MyGameObject("Obo");
	m_Object2->Start();
	m_Object2->SetSpeed(-0.005);
	m_Object2->GetComponent<Transform>()->Translate(glm::vec3(200, 0, 0));

	m_Camera = new Camera();

	Renderer::SetCurrentCamera(m_Camera);
}

void GameWindow::Update(float deltaTime)
{
	m_Object->Update(deltaTime);
	m_Object2->Update(deltaTime);

	BoxCollider* firstBox = m_Object->GetComponent<BoxCollider>();
	BoxCollider* secondBox = m_Object2->GetComponent<BoxCollider>();

	//std::cout << "Obj1: " << firstBox->GetMin().x << " " << firstBox->GetMin().y << std::endl;
	//std::cout << "Obj2: " << secondBox->GetMin().x << " " << secondBox->GetMin().y << std::endl;

	if (firstBox->HasCollision(secondBox)) 
	{
		std::cout << "Collision!\n";
	}
	else
	{
		std::cout << "Not Collide!\n";
	}

	Renderer::DrawObject(m_Object);
	Renderer::DrawObject(m_Object2);
}

GameWindow::~GameWindow()
{
	delete m_Object;
	delete m_Camera;
}
