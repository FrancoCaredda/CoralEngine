#include "GameWindow.h"

#include "Core/Graphics/Renderer/Renderer.h"

#include <iostream>

GameWindow::GameWindow(const std::string& title, int width, int height, const CoralMonitor& monitor)
	: AWindow(title, width, height, monitor)
{
}

void GameWindow::Start()
{
	Shader fragmentShader(GL_FRAGMENT_SHADER);
	Shader vertexShader(GL_VERTEX_SHADER);

	fragmentShader.Load("Assets/Shaders/Rectangle.frag.glsl");
	vertexShader.Load("Assets/Shaders/Rectangle.vert.glsl");

	fragmentShader.Compile();
	vertexShader.Compile();

	m_Program = new ShaderProgram();
	m_Program->AttachShader(fragmentShader);
	m_Program->AttachShader(vertexShader);

	m_Program->Link();

	m_Sprite = new Sprite(m_Program);	
	Renderer::PushTarget(m_Sprite);
}

void GameWindow::Update(float deltaTime)
{
	Renderer::DrawSpriteArrays();
}

GameWindow::~GameWindow()
{
	delete m_Program;
	delete m_Sprite;
}
