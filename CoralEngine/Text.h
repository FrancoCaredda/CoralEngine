#ifndef TEXT_H
#define TEXT_H

#include "GameObjects/GameObject.h"
#include "Core/Asset.h"

class Text : public AGameObject
{
public:
	Text(const std::string& name)
		: AGameObject(name) { }

	virtual ~Text() override {}
private:
	std::string m_Text;
	AssetHandle m_Font;
};

#endif
