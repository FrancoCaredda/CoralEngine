#include "AssetManager.h"

#include "Texture.h"

#include <vector>

AssetManager AssetManager::s_Instance;

bool AssetManager::Init()
{
    s_Instance.m_Inited = true;
    return true;
}

bool AssetManager::LoadTexture(const std::string& texture, int slot) noexcept
{
    std::string name = s_Instance.AssetName(texture);
    
    try
    {
        s_Instance.m_Table[name] = AssetHandle(new Texture(texture, slot), slot);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

AssetHandle AssetManager::GetAssetHandle(const std::string& name) noexcept
{
    return s_Instance.m_Table[name];
}

void AssetManager::UnloadAsset(const std::string& name) noexcept
{

}

void AssetManager::Shutdown()
{
    for (auto i = s_Instance.m_Table.begin(); i != s_Instance.m_Table.end(); i++)
        i->second.Delete();

    s_Instance.m_Table.clear();
}

std::string AssetManager::AssetName(const std::string& path) const noexcept
{
    std::vector<std::string> Array;

    std::string copy = path;
    char* tempPath = const_cast<char*>(copy.c_str());
    const char* delims = ".\\/";

    char* temp = strtok(tempPath, delims);

    while (temp != nullptr)
    {
        Array.push_back(temp);
        temp = strtok(nullptr, delims);
    }

    return Array[Array.size() - 2];
}
