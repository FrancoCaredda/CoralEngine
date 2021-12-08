#include "Sprite.h"

Sprite::Sprite(AGameObject* owner, ShaderProgram* shader)
{
	if (shader != nullptr)
		m_Program = shader;
	else
		m_Program = nullptr;

	m_VertexBuffer = new VertexBufferObject(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	m_VertexBuffer->Bind();

	/*m_VertexBuffer->SendData({
		//-0.5f, -0.5f,
		//-0.5f, 0.5f,
		// 0.5f, -0.5f,
		// 0.5f, -0.5f,
		//-0.5f, 0.5f,
		// 0.5f, 0.5f
		50.0f, 50.0f,
		50.0f, 100.0f,
		100.0f, 50.0f,
		100.0f, 50.0f,
		50.0f, 100.0f,
		100.0f, 100.0f
	});*/

	m_VertexBuffer->SendData({
		0.0f,	0.0f,
		0.0f,	50.0f,
		50.0f,	0.0f,
		50.0f,	0.0f,
		0.0f,	50.0f,
		50.0f,	50.0f
		});
	
	m_VertexBuffer->Unbind();

	m_VertexArray = new VertexArrayObject();

	m_Owner = owner;
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

void Sprite::SetShaderProgram(ShaderProgram* program) noexcept
{
	m_Program = program;
}

Sprite::~Sprite()
{
	delete m_VertexArray;
	delete m_VertexBuffer;

	m_Program = nullptr;
}
