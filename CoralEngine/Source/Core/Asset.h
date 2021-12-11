#ifndef ASSET_H
#define ASSET_H

#include "defines.h"

class IAsset
{
public:
	virtual void Bind() const noexcept = 0;
	virtual void Unbind() const noexcept = 0;

	virtual ~IAsset() { }
};

class CORAL_API AssetHandle
{
public:
	AssetHandle() = default;
	AssetHandle(IAsset* asset, int data);

	void Bind() const noexcept;
	void Unbind() const noexcept;

	inline int GetData() const noexcept { return m_Data; }

	bool operator==(std::nullptr_t pointer) const noexcept;
	bool operator!=(std::nullptr_t pointer) const noexcept;

	void Delete();

	template<typename T>
	friend T GetHiddenData(const AssetHandle&);

	~AssetHandle();
private:
	IAsset* m_Asset = nullptr;
	int m_Data = 0;
};

// T must be a pointer
template<typename T>
T GetHiddenData(const AssetHandle& handle)
{
//	return dynamic_cast<T*>(handle.m_Asset);
	return nullptr;
}

#endif
