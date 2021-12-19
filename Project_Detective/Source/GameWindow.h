#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "Core/AWindow.h"

#include "Components/Sprite.h"

#include "Core/Shader.h"
#include "GameObjects/Camera.h"

#include "MyGameObject.h"

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <windows.h>

class GameWindow : public AWindow
{
public:
	GameWindow(const std::string& title, int width, int height, const CoralMonitor& monitor);

	virtual void Start() override;
	virtual void Update(float deltaTime) override;

	void createSocket();
	void newProcess();

	virtual ~GameWindow() override;
private:
	Camera* m_Camera;

	MyGameObject** m_ObjetctsList;
	int m_ObjectsCount = 0;


	WSAData wsaData;
	int sizeofaddr;
	WORD DLLVersion;
	SOCKADDR_IN addr;
	SOCKET sListen;
	SOCKET newConnection;
	STARTUPINFOA m_starupInfo;
	PROCESS_INFORMATION m_ProcessInfo;
};

#endif // !GAME_WINDOW_H
