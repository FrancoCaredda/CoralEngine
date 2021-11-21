#ifndef SPRITE_H
#define SPRITE_H

#include "defines.h"

#include "GameObjects/GameObject.h"

#include "Core/VertexArrayObject.h"
#include "Core/VertexBufferObject.h"

#include "Core/Shader.h"
#include "Core/ShaderProgram.h"

class CORAL_API Sprite
{
public:
	Sprite(AGameObject* owner, ShaderProgram* shader = nullptr);

	void Bind();
	void Unbind();

	void SetShaderProgram(ShaderProgram*) noexcept;
	inline ShaderProgram* GetShaderProgram() const noexcept { return m_Program; }

	~Sprite();
private:
	ShaderProgram* m_Program;
	VertexArrayObject* m_VertexArray;
	VertexBufferObject* m_VertexBuffer;

	AGameObject* m_Owner;

	// TODO: ADD TEXTURES
};

#endif // !SPRITE_H
