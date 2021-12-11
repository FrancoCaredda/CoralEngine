#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "defines.h"

#include "Asset.h"
#include "Shader.h"

#include <unordered_map>
#include <string>

class CORAL_API AssetManager
{
public:
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(AssetManager&) = delete;

	static bool Init();

	static bool LoadTexture(const std::string& texture, int slot) noexcept;
	static bool LoadFont(const std::string& font, int slot) noexcept;
	static AssetHandle GetAssetHandle(const std::string& name) noexcept;

	static void UnloadAsset(const std::string& name) noexcept;

	static FT_Library GetFTLibrary() noexcept;

	static void Shutdown();
private:
	AssetManager() = default;
	std::string AssetName(const std::string& path) const noexcept;
private:
	static AssetManager s_Instance;
	bool m_Inited = false;

	FT_Library m_FTLibrary;

	std::unordered_map<std::string, AssetHandle> m_Table;
};

#endif // !ASSET_MANAGER_H
