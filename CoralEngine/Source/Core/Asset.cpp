#include "Asset.h"

AssetHandle::AssetHandle(IAsset* asset, int data)
{
	m_Asset = asset;
	m_Data = data;
}

void AssetHandle::Bind() const noexcept
{
	m_Asset->Bind();
}

void AssetHandle::Unbind() const noexcept
{
	m_Asset->Unbind();
}

bool AssetHandle::operator==(std::nullptr_t pointer) const noexcept
{
	return m_Asset == pointer;
}

bool AssetHandle::operator!=(std::nullptr_t pointer) const noexcept
{
	return m_Asset != pointer;
}

void AssetHandle::Delete()
{
	delete m_Asset;
}

AssetHandle::~AssetHandle()
{
	//delete m_Asset;
}
