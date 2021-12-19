#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "GameWindow.h"

#include "Core/Renderer.h"

#include <iostream>
#include <string>
#include <Components/BoxCollider.h>
#include "Core/AssetManager.h"

GameWindow::GameWindow(const std::string& title, int width, int height, const CoralMonitor& monitor)
	: AWindow(title, width, height, monitor)
{
}

void GameWindow::Start()
{
	newProcess();

	AssetManager::LoadTexture("Assets\\Textures\\smile.png", 0);
	Renderer::ClearColor(1.0, 1.0, 1.0, 1.0);
	m_ObjetctsList = new MyGameObject * [4];
	m_ObjectsCount = 4;

	m_ObjetctsList[0] = new MyGameObject("Floor");
	m_ObjetctsList[0]->GetTransform()->Scale(glm::vec3(12, 1, 1));
	m_ObjetctsList[0]->Start();
	m_ObjetctsList[0]->GetComponent<BoxCollider>()->ShrinkToSize();
	PhysicsComponent* floorPhysics = m_ObjetctsList[0]->GetComponent<PhysicsComponent>();
	floorPhysics->SetMass(0);
	floorPhysics->SetVelocity(0, 0);

	floorPhysics->SetElasticity(1);

	m_ObjetctsList[1] = new MyGameObject("Obo");
	m_ObjetctsList[1]->Start();
	PhysicsComponent* oboPhysics = m_ObjetctsList[1]->GetComponent<PhysicsComponent>();
	oboPhysics->SetMass(10);
	//oboPhysics->SetVelocity(100, 0);
	m_ObjetctsList[1]->GetComponent<Transform>()->Translate(glm::vec3(98, 300, 0));

	oboPhysics->SetElasticity(1);

	m_ObjetctsList[2] = new MyGameObject("Box1");
	m_ObjetctsList[2]->Start();
	PhysicsComponent* box1Phys = m_ObjetctsList[2]->GetComponent<PhysicsComponent>();
	box1Phys->SetMass(10);
	//box1Phys->SetVelocity(-10, 0);
	m_ObjetctsList[2]->GetComponent<Transform>()->Translate(glm::vec3(49, 200, 0));

	box1Phys->SetElasticity(1);


	m_ObjetctsList[3] = new MyGameObject("Box2");
	m_ObjetctsList[3]->Start();
	PhysicsComponent* box2Phys = m_ObjetctsList[3]->GetComponent<PhysicsComponent>();
	//box2Phys->SetVelocity(-80, 200);
	m_ObjetctsList[3]->GetComponent<Transform>()->Translate(glm::vec3(0, 51, 0));

	box2Phys->SetElasticity(1);
	box2Phys->SetMass(0);
	box2Phys->SetVelocity(100, 0);

	m_Camera = new Camera();

	Renderer::SetCurrentCamera(m_Camera);

	createSocket();
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
				std::cout << "Collision!\n";
				Manifold m = firstBox->GetManifoldWith(*secondBox);

				PhysicsComponent::ResolveCollision(m);
				PhysicsComponent::PositionalCorrection(m);
			}
			else
			{
				std::cout << "Not Collide!\n";
			}
		}
	}

	for (int i = 0; i < m_ObjectsCount; i++)
	{
		Renderer::DrawObject(m_ObjetctsList[i]);
	}


	if (newConnection != 0) {
		for (int i = 0; i < 4; i++) {
			std::string msg = m_ObjetctsList[i]->GetName();
			glm::vec3 a = m_ObjetctsList[i]->GetComponent<Transform>()->GetPosition();
			msg += " " + std::to_string(a.x) + " " + std::to_string(a.y);
			a = m_ObjetctsList[i]->GetComponent<Transform>()->GetSize();
			msg += " " + std::to_string(a.x) + " " + std::to_string(a.y) + " " + std::to_string(a.z);

			int msg_size = msg.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);
		}

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

void GameWindow::createSocket() {
	/*WSAData*/ wsaData;
	/*WORD*/ DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	/*SOCKADDR_IN*/ addr;
	/*int*/ sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	/*SOCKET*/ sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

}

void GameWindow::newProcess() {
	ZeroMemory(&m_starupInfo, sizeof(STARTUPINFOA));
	ZeroMemory(&m_ProcessInfo, sizeof(PROCESS_INFORMATION));

	CreateProcessA(
		"D:/OS/CoralEngine/Client/Cl/Debug/Cl.exe",
		NULL,
		NULL,
		NULL,
		false,
		CREATE_NEW_CONSOLE,
		nullptr,
		"D:/OS/CoralEngine/Debug",
		&m_starupInfo,
		&m_ProcessInfo
	);
}
