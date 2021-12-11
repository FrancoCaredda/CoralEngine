#include "GameWindow.h"

#include "Core/Renderer.h"
#include "Core/AssetManager.h"

#include <iostream>
#include <cstdlib>
#include <ctime>


GameWindow::GameWindow(const std::string& title, int width, int height, const CoralMonitor& monitor)
	: AWindow(title, width, height, monitor)
{
}

void GameWindow::Start()
{
	if (!AssetManager::LoadTexture("Assets\\Texturessmiling-face.png", 0))
		std::cout << "Something went wrong!" << std::endl;
		
	if (!AssetManager::LoadTexture("Assets\\Texturessmile.png", 1))
		std::cout << "Something went wrong!" << std::endl;

	for (int i = 0; i < 18; i++)
		m_Objects.push_back(new MyGameObject("Bob"));
	
	for (int i = 0; i < 18; i++)
		m_Objects[i]->Start();

	srand(time(0));

	for (int i = 0; i < 18; i++)
	{
		int x = rand() % m_Width;
		int y = rand() % m_Height;

		m_Objects[i]->GetComponent<Transform>()->Translate(glm::vec3(x / 2.0 - 50.0 / 2.0, y / 2.0 - 50.0 / 2.0, 0.0));
	}

	m_Camera = new Camera();

	m_Object = new MyGameObject2("Carl");
	m_Object->Start();

	Renderer::SetCurrentCamera(m_Camera);
}

void GameWindow::Update(float deltaTime)
{
	Renderer::ClearColor(0.5, 0.25, 0.1, 1);
	for (int i = 0; i < 18; i++)
		m_Objects[i]->Update(deltaTime);

	m_Object->Update(deltaTime);

	for (int i = 0; i < 18; i++)
		Renderer::DrawObject(m_Objects[i]);

	Renderer::DrawObject(m_Object);
}

GameWindow::~GameWindow()
{
	for (int i = 0; i < 18; i++)
		delete m_Objects[i];

	delete m_Camera;
}
