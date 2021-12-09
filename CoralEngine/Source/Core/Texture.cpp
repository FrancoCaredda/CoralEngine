#include "Texture.h"

Texture::Texture(const std::string& textureName, int slot)
	: m_Slot(slot)
{
	int x, y, channels;

	stbi_set_flip_vertically_on_load(true);
	m_Data = stbi_load(textureName.c_str(), &x, &y, &channels, 4);

	if (m_Data == nullptr)
		throw std::exception("Texture wasn\'t loaded!");

	glActiveTexture(GL_TEXTURE0 + m_Slot);
	glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);

	glBindTexture(GL_TEXTURE_2D, m_Id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const noexcept
{
	glActiveTexture(GL_TEXTURE0 + m_Slot);
	glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture::Unbind() const noexcept
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	stbi_image_free(m_Data);
	glDeleteTextures(1, &m_Id);
}
