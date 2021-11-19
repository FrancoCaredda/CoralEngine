#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "Core/Window/AWindow.h"

#include "Core/Graphics/Sprite/Sprite.h"

#include "Core/Graphics/Shaders/Shader.h"
#include "Core/Graphics/Shaders/ShaderProgram.h"

class GameWindow : public AWindow
{
public:
	GameWindow(const std::string& title, int width, int height, const CoralMonitor& monitor);

	virtual void Start() override;
	virtual void Update(float deltaTime) override;

	virtual ~GameWindow() override;
private:
	Sprite* m_Sprite;
	ShaderProgram* m_Program;
};

#endif // !GAME_WINDOW_H
