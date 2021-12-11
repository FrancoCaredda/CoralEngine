#include "Core/Application.h"
#include "GameWindow.h"

int main(void)
{
	if (!Application::Init())
		return -1;

	GameWindow window("Sandbox", 1200, 900, Application::GetNullMonitor());

	Application::SetCurrentWindow(&window);
	Application::MakeContextCurrent();

	if (!Application::InitGL())
		return -2;

	Application::Start();
	Application::RunLoop();

	Application::Shutdown();

	return 0;
}