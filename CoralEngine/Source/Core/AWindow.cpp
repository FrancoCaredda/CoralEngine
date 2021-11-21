#include "AWindow.h"

AWindow::AWindow(const std::string& title, int width, int height, const CoralMonitor& monitor)
	: m_Width(width), m_Height(height), m_Title(title), m_Monitor(monitor)
{
	m_Context = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), m_Monitor.m_Monitor, nullptr);
}

void AWindow::SetTitle(const std::string& title) noexcept
{
	m_Title = title;
}

void AWindow::SetWidth(int width) noexcept
{
	m_Width = width;
}

void AWindow::SetHeight(int height) noexcept
{
	m_Height = height;
}

AWindow::~AWindow()
{
	glfwDestroyWindow(m_Context);
}
