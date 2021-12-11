#ifndef FONT_H
#define FONT_H

#include "defines.h"
#include "Asset.h"
#include "AssetManager.h"

#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

#include <map>
 
#define MAX_CHARACTER_ASCII 128

class Font : public IAsset
{
private:
	struct Character
	{
		uint32_t TextureID;
		glm::ivec2 Size; 
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		uint32_t Advance;      // Offset to advance to next glyph
	};
public:
	Font(const std::string& fontName);

	virtual void Bind() const noexcept override;
	virtual void Unbind() const noexcept override;

	inline FT_Face GetFace() const noexcept { return m_Face; }

	virtual ~Font() override;
private:
	FT_Face m_Face;
	std::map<char, Character> m_Glyphs;

	VertexArrayObject* m_VAO;
	VertexBufferObject* m_VBO;

	mutable bool m_Bind;
};

#endif // !FONT_H