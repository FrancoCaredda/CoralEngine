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

	m_VertexArray = new VertexArrayObject();
	m_VertexArray->Bind();

	m_VertexBuffer = new VertexBufferObject(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	m_VertexBuffer->Bind();

	m_IndexBuffer = new IndexBufferObject(GL_STATIC_DRAW);
	m_IndexBuffer->Bind();

	m_VertexBuffer->SendData({
		0.0f, 0.0f,		0.0f, 0.0f,
		0.0f, 50.0f,	0.0f, 1.0f,
		50.0f, 0.0f,	1.0f, 0.0f,
		50.0f, 50.0f,	1.0f, 1.0f
	});

	m_IndexBuffer->SendData({0, 1, 2, 2, 1, 3});

	m_VertexArray->SetVertexAttribs({
		{0, {2, 4, 0}},
		{1, {2, 4, 2}}
	});

	m_VertexBuffer->Unbind();
	m_IndexBuffer->Unbind();
	m_VertexArray->Unbind();
	m_Owner = owner;
}

void Sprite::Bind()
{
	m_VertexArray->Bind();
	m_VertexBuffer->Bind();
	m_IndexBuffer->Bind();

	m_Shader->Bind();
	
	if (m_TextureHandle != nullptr)
		m_TextureHandle.Bind();
}

void Sprite::Unbind()
{
	m_VertexArray->Unbind();
	m_VertexBuffer->Unbind();
	m_Shader->Unbind();

	if (m_TextureHandle != nullptr)
		m_TextureHandle.Unbind();
}

void Sprite::SetColor(const glm::vec4& color) noexcept
{
	m_Color = color;
}

void Sprite::SetTexture(const AssetHandle& textureHandle)
{
	m_TextureHandle = textureHandle;
}

Sprite::~Sprite()
{
	delete m_VertexArray;
	delete m_VertexBuffer;
	delete m_Shader;
}
