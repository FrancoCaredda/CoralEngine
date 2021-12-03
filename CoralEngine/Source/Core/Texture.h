#ifndef TEXTURE_H
#define TEXTURE_H

#include "defines.h"
#include "stb_image.h"

#include <string>

class Texture
{
public:
	Texture(const std::string& textureName, int slot);
	Texture(const Texture&) = delete;

	void Bind();
	void Unbind();

	inline int GetSlot() const noexcept { return m_Slot; }

	~Texture();
private:
	uint32_t m_Id;
	uint8_t* m_Data;
	int m_Slot;
};

#endif // !TEXTURE_H
