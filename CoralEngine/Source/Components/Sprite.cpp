#include "Sprite.h"

Sprite::Sprite(AGameObject* owner)
{
	try
	{
		m_Shader = new Shader();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		m_Shader = nullptr;
	}

	m_VertexBuffer = new VertexBufferObject(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	m_VertexBuffer->Bind();

	m_VertexBuffer->SendData({
		50.0f, 50.0f,
		50.0f, 100.0f,
		100.0f, 50.0f,
		100.0f, 50.0f,
		50.0f, 100.0f,
		100.0f, 100.0f
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

	if (m_Shader != nullptr)
		m_Shader->Bind();
}

void Sprite::Unbind()
{
	m_VertexArray->Unbind();
	m_VertexBuffer->Unbind();
	m_Shader->Unbind();
}

void Sprite::SetColor(const glm::vec4& color) noexcept
{
	m_Color = color;
}

Sprite::~Sprite()
{
	delete m_VertexArray;
	delete m_VertexBuffer;
	delete m_Shader;
}
