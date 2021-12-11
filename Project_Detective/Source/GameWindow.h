#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "Core/AWindow.h"

#include "Components/Sprite.h"

#include "Core/Shader.h"
#include "GameObjects/Camera.h"

#include "MyGameObject.h"

#include "MyGameObject2.h"

class GameWindow : public AWindow
{
public:
	GameWindow(const std::string& title, int width, int height, const CoralMonitor& monitor);

	virtual void Start() override;
	virtual void Update(float deltaTime) override;

	virtual ~GameWindow() override;
private:
	Camera* m_Camera;
	std::vector<MyGameObject*> m_Objects;
	MyGameObject2* m_Object;
};

#endif // !GAME_WINDOW_H
