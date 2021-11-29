#include "GameWindow.h"

#include "Core/Renderer.h"

#include <iostream>

GameWindow::GameWindow(const std::string& title, int width, int height, const CoralMonitor& monitor)
	: AWindow(title, width, height, monitor)
{
}

void GameWindow::Start()
{
	m_Object = new MyGameObject("Bob");
	m_Object->Start();
	m_Camera = new Camera();

	Renderer::SetCurrentCamera(m_Camera);
}

void GameWindow::Update(float deltaTime)
{
	m_Object->Update(deltaTime);
	std::cout << deltaTime << std::endl;

	Renderer::DrawObject(m_Object);
}

GameWindow::~GameWindow()
{
	delete m_Object;
	delete m_Camera;
}
