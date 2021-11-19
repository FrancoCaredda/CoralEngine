#ifndef RENDERER_H
#define RENDERER_H

#include "defines.h"

#include "Core/Graphics/Buffers/VertexArrayObject.h"
#include "Core/Graphics/Buffers/VertexBufferObject.h"

#include "Core/Graphics/Shaders/Shader.h"
#include "Core/Graphics/Shaders/ShaderProgram.h"

#include "Core/Graphics/Sprite/Sprite.h"

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

private:
	Renderer() = default;
	Renderer(const Renderer&) = delete;
private:
	static Renderer s_Instance;
	std::list<Sprite*> m_Targets;
};

#endif // !RENDERER_H