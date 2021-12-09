#ifndef TEXTURE_H
#define TEXTURE_H

#include "defines.h"
#include "stb_image.h"

#include "Asset.h"

#include <string>

class Texture : public IAsset
{
public:
	Texture(const std::string& textureName, int slot);
	Texture(const Texture&) = delete;

	virtual void Bind() const noexcept override;
	virtual void Unbind() const noexcept override;

	inline int GetSlot() const noexcept { return m_Slot; }

	virtual ~Texture() override;
private:
	uint32_t m_Id;
	uint8_t* m_Data;
	int m_Slot;
};

#endif // !TEXTURE_H
