#include "Application.h"

#include "Renderer.h"

#include <iostream>

#include <ctime>

Application Application::s_Application;

Application& Application::Get() noexcept
{
	return s_Application;
}

bool Application::Init() noexcept
{
	if (!glfwInit())
	{
		std::cerr << "Glfw wasn\'t initialized!";
		return false;
	}

	return true;
}

bool Application::InitGL() noexcept
{
	if (glewInit())
	{
		std::cerr << "Glew wasn\'t initialized!";
		return false;
	}

	Renderer::Init();

	glEnable(GL_DEPTH_TEST);

	return true;
}

CoralMonitor Application::GetNullMonitor() noexcept
{
	CoralMonitor monitor;
	monitor.m_Monitor = nullptr;
	return monitor;
}

CoralMonitor Application::GetCurrentMonitor() noexcept
{
	CoralMonitor monitor;
	monitor.m_Monitor = glfwGetPrimaryMonitor();

	return monitor;
}

void Application::SetCurrentWindow(AWindow* window) noexcept
{
	s_Application.m_Window = window;
}

void Application::MakeContextCurrent() noexcept
{
	glfwMakeContextCurrent(s_Application.m_Window->m_Context);
}

void Application::Start() noexcept
{
	s_Application.m_Window->Start();
}

void Application::RunLoop() noexcept
{
	float deltaTime;
	float previousTime = 0;

	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(s_Application.m_Window->m_Context))
	{
		Renderer::Clear();

		deltaTime = (glfwGetTime() - previousTime);
		previousTime += deltaTime;

		s_Application.m_Window->Update(deltaTime);

		glfwPollEvents();
		glfwSwapBuffers(s_Application.m_Window->m_Context);
	}
}

void Application::Shutdown() noexcept
{
	Renderer::Shutdown();
	glfwTerminate();
}


