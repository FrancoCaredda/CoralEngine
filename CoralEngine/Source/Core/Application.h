#ifndef APPLICATION_H
#define APPLICATION_H

#include "defines.h"

#include "Core/AWindow.h"
#include "Core/Types.h"

class CORAL_API Application
{
public:
	static Application& Get() noexcept;
	static bool Init() noexcept;
	static bool InitGL() noexcept;

	static CoralMonitor GetNullMonitor() noexcept;
	static CoralMonitor GetCurrentMonitor() noexcept;

	static void SetCurrentWindow(AWindow* window) noexcept;
	static void MakeContextCurrent() noexcept;

	static void Start() noexcept;
	static void RunLoop() noexcept;

	static void Shutdown() noexcept;
private:
	Application() = default;
	Application(const Application& application) = default;
private:
	static Application s_Application;
	AWindow* m_Window;
};

#endif // !APPLICATION_H
