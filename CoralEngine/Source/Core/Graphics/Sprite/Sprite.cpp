#include "Sprite.h"

Sprite::Sprite(ShaderProgram* shader)
{
	m_Program = shader;

	m_VertexBuffer = new VertexBufferObject(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	m_VertexBuffer->Bind();

	m_VertexBuffer->SendData({
		-0.5f, -0.5f,
		-0.5f, 0.5f,
		 0.5f, -0.5f,
		 0.5f, -0.5f,
		-0.5f, 0.5f,
		 0.5f, 0.5f
	});
	
	m_VertexBuffer->Unbind();

	m_VertexArray = new VertexArrayObject();
}

void Sprite::Bind()
{
	m_VertexArray->Bind();

	m_VertexArray->SetVertexAttribs({
		{0, {2, 2, 0}}
	});

	m_VertexBuffer->Bind();
	m_Program->Use();
}

void Sprite::Unbind()
{
	m_VertexArray->Unbind();
	m_VertexBuffer->Unbind();
	m_Program->Unuse();
}

Sprite::~Sprite()
{
	delete m_VertexArray;
	delete m_VertexBuffer;

	m_Program = nullptr;
}
