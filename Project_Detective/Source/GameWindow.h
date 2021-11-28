#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "Core/AWindow.h"

#include "Components/Sprite.h"

#include "Core/Shader.h"
#include "GameObjects/Camera.h"
#include "Core/ShaderProgram.h"

#include "MyGameObject.h"

class GameWindow : public AWindow
{
public:
	GameWindow(const std::string& title, int width, int height, const CoralMonitor& monitor);

	virtual void Start() override;
	virtual void Update(float deltaTime) override;

	virtual ~GameWindow() override;
private:
	Camera* m_Camera;
	MyGameObject* m_Object;
	MyGameObject* m_Object2;
};

#endif // !GAME_WINDOW_H
