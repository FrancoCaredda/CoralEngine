#ifndef AWINDOW_H
#define AWINDOW_H

#include "defines.h"
#include "Core/Types.h"


#include <string>

class CORAL_API AWindow
{
public:
	AWindow(const AWindow&) = delete;
	AWindow(const std::string& title, int width, int height, const CoralMonitor& monitor);

	void SetTitle(const std::string& title) noexcept;
	inline std::string GetTitle() const noexcept { return m_Title; }

	void SetWidth(int width) noexcept;
	inline int GetWidth() const noexcept { return m_Width; }
	
	void SetHeight(int height) noexcept;
	inline int GetHeight() const noexcept { return m_Height; }

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;

	virtual ~AWindow();

	friend class Application;
private:
	GLFWwindow* m_Context;
protected:
	CoralMonitor m_Monitor;

	int m_Width;
	int m_Height;

	std::string m_Title;
};

#endif // !AWINDOW_H