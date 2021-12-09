#ifndef RENDERER_H
#define RENDERER_H

#include "defines.h"

#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"

#include "Core/VertexArrayObject.h"
#include "Core/VertexBufferObject.h"

#include "Core/Shader.h"

#include "Components/Sprite.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <list>

class CORAL_API Renderer
{
public:
#ifdef _DEBUG
	enum RenderMode { FILL = 0, LINE = 1, POINT = 2 };
#endif // _DEBUG

	static void Init() noexcept;

	static Renderer& Get() noexcept;

	static void Clear() noexcept;
	static void ClearColor(float r, float g, float b, float a) noexcept;

#ifdef _DEBUG
	static void Mode(RenderMode mode) noexcept;
#endif // _DEBUG

	static void SetCurrentCamera(Camera* camera) noexcept;
	static void DrawObject(AGameObject* object) noexcept;

	static void Shutdown() noexcept;
private:
	Renderer() = default;
	Renderer(const Renderer&) = delete;
private:
	static Renderer s_Instance;

	Camera* m_Camera;
	glm::mat4 m_Projection;
};

#endif // !RENDERER_H