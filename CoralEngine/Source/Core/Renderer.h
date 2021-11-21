#ifndef RENDERER_H
#define RENDERER_H

#include "defines.h"

#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"

#include "Core/VertexArrayObject.h"
#include "Core/VertexBufferObject.h"

#include "Core/Shader.h"
#include "Core/ShaderProgram.h"

#include "Components/Sprite.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <list>

class CORAL_API Renderer
{
public:
	static Renderer& Get() noexcept;

	static void Clear() noexcept;
	static void ClearColor(float r, float g, float b, float a) noexcept;

	static void PushTarget(Sprite* target) noexcept;
	static void PopTarget() noexcept;

	static void DrawSpriteArrays() noexcept;
	static void DrawSpriteIndecies() noexcept;

	static void Init() noexcept;

	static void SetCurrentCamera(Camera* camera) noexcept;
	static void DrawObject(AGameObject* object) noexcept;

private:
	Renderer() = default;
	Renderer(const Renderer&) = delete;
private:
	static Renderer s_Instance;
	std::list<Sprite*> m_Targets;

	Camera* m_Camera;

	glm::mat4 m_Projection;
};

#endif // !RENDERER_H