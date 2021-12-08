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
	m_ObjetctsList = new MyGameObject * [4];
	m_ObjectsCount = 4;

	m_ObjetctsList[0] = new MyGameObject("Floor");
	m_ObjetctsList[0]->GetTransform()->Scale(glm::vec3(12, 1, 1));
	m_ObjetctsList[0]->Start();
	m_ObjetctsList[0]->GetComponent<BoxCollider>()->ShrinkToSize();
	PhysicsComponent* floorPhysics = m_ObjetctsList[0]->GetComponent<PhysicsComponent>();
	floorPhysics->SetMass(0);
	floorPhysics->SetVelocity(0, 0);

	m_ObjetctsList[1] = new MyGameObject("Obo");
	m_ObjetctsList[1]->Start();
	PhysicsComponent* oboPhysics = m_ObjetctsList[1]->GetComponent<PhysicsComponent>();
	oboPhysics->SetMass(10);
	//oboPhysics->SetVelocity(100, 0);
	m_ObjetctsList[1]->GetComponent<Transform>()->Translate(glm::vec3(98, 300, 0));

	m_ObjetctsList[2] = new MyGameObject("Box1");
	m_ObjetctsList[2]->Start();
	PhysicsComponent* box1Phys = m_ObjetctsList[2]->GetComponent<PhysicsComponent>();
	box1Phys->SetMass(10);
	//box1Phys->SetVelocity(-10, 0);
	m_ObjetctsList[2]->GetComponent<Transform>()->Translate(glm::vec3(49, 200, 0));

	m_ObjetctsList[3] = new MyGameObject("Box2");
	m_ObjetctsList[3]->Start();
	PhysicsComponent* box2Phys = m_ObjetctsList[3]->GetComponent<PhysicsComponent>();
	box2Phys->SetMass(20);
	//box2Phys->SetVelocity(-80, 200);
	m_ObjetctsList[3]->GetComponent<Transform>()->Translate(glm::vec3(0, 100, 0));

	m_Camera = new Camera();

	Renderer::SetCurrentCamera(m_Camera);
}

void GameWindow::Update(float deltaTime)
{
	for (int i = 0; i < m_ObjectsCount; i++)
	{
		m_ObjetctsList[i]->Update(deltaTime);
	}

	for (int i = 0; i < m_ObjectsCount; i++)
	{
		BoxCollider* firstBox = m_ObjetctsList[i]->GetComponent<BoxCollider>();

		for (int j = i+1; j < m_ObjectsCount; j++)
		{
			BoxCollider* secondBox = m_ObjetctsList[j]->GetComponent<BoxCollider>();

			if (firstBox->HasCollision(*secondBox))
			{
				//std::cout << "Collision!\n";
				Manifold m = firstBox->GetManifoldWith(*secondBox);

				PhysicsComponent::ResolveCollision(m);
				PhysicsComponent::PositionalCorrection(m);
			}
			else
			{
				//std::cout << "Not Collide!\n";
			}
		}
	}

	for (int i = 0; i < m_ObjectsCount; i++)
	{
		Renderer::DrawObject(m_ObjetctsList[i]);
	}
}

GameWindow::~GameWindow()
{
	for (int i = 0; i < m_ObjectsCount; i++)
	{
		m_ObjetctsList[i];
	}

	delete[] m_ObjetctsList;

	delete m_Camera;
}
