#ifndef SPRITE_H
#define SPRITE_H

#include "defines.h"

#include "Core/Graphics/Buffers/VertexArrayObject.h"
#include "Core/Graphics/Buffers/VertexBufferObject.h"

#include "Core/Graphics/Shaders/Shader.h"
#include "Core/Graphics/Shaders/ShaderProgram.h"

class CORAL_API Sprite
{
public:
	Sprite(ShaderProgram* shader);

	void Bind();
	void Unbind();

	~Sprite();
private:
	ShaderProgram* m_Program;
	VertexArrayObject* m_VertexArray;
	VertexBufferObject* m_VertexBuffer;

	// TODO: ADD TEXTURES
};

#endif // !SPRITE_H
