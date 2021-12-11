#include "Font.h"

#include <exception>

Font::Font(const std::string& fontName)
{
	if (FT_New_Face(AssetManager::GetFTLibrary(), fontName.c_str(), 0, &m_Face))
	{
		std::string message = "[ERROR] FreeType: can't load font: " + fontName;
		throw std::exception(message.c_str());
	}

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (uint8_t i = 0; i < 128; i++)
    {
        if (FT_Load_Char(m_Face, i, FT_LOAD_RENDER))
        {
            std::cout << "[ERROR] FreeType: Failed to load Glyph" << std::endl;
            continue;
        }

        uint32_t texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            m_Face->glyph->bitmap.width,
            m_Face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            m_Face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
            glm::ivec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
            m_Face->glyph->advance.x
        };
        
        m_Glyphs.insert({(char)i, character});
    }
}

void Font::Bind() const noexcept
{
	m_Bind = true;
}

void Font::Unbind() const noexcept
{
	m_Bind = false;
}

Font::~Font()
{
    FT_Done_Face(m_Face);
}
