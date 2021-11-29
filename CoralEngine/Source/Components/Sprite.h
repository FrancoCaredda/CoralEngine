#ifndef SPRITE_H
#define SPRITE_H

#include "defines.h"

#include "GameObjects/GameObject.h"

#include "Core/VertexArrayObject.h"
#include "Core/VertexBufferObject.h"

#include "Core/Shader.h"

#include "glm/glm.hpp"

class CORAL_API Sprite
{
public:
	Sprite(AGameObject* owner);

	void Bind();
	void Unbind();

	void SetColor(const glm::vec4& color) noexcept;
	inline glm::vec4 GetColor() const noexcept { return m_Color; }

	~Sprite();

	friend class Renderer;
private:
	Shader* m_Shader;
	VertexArrayObject* m_VertexArray;
	VertexBufferObject* m_VertexBuffer;

	AGameObject* m_Owner;

	glm::vec4 m_Color;

	// TODO: ADD TEXTURES
};

#endif // !SPRITE_H
