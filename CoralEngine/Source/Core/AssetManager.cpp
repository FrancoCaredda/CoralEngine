#include "AssetManager.h"

#include "Texture.h"
#include "Font.h"

#include <vector>

AssetManager AssetManager::s_Instance;

bool AssetManager::Init()
{
    //if (FT_Init_FreeType(&s_Instance.m_FTLibrary))
    //{
    //    std::cout << "[ERROR] FREETYPE: Could not init FreeType Library" << std::endl;
    //    s_Instance.m_Inited = false;

    //    return false;
    //}

    s_Instance.m_Inited = true;
    return true;
}

bool AssetManager::LoadTexture(const std::string& texture, int slot) noexcept
{
    if (!s_Instance.m_Inited)
        return false;

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

bool AssetManager::LoadFont(const std::string& font, int slot) noexcept
{
    if (!s_Instance.m_Inited)
        return false;

    std::string name = s_Instance.AssetName(font);

    try
    {
        s_Instance.m_Table[name] = AssetHandle(new Font(font), slot);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}

AssetHandle AssetManager::GetAssetHandle(const std::string& name) noexcept
{
    //if (!s_Instance.m_Inited)
    //    return;

    return s_Instance.m_Table[name];
}

void AssetManager::UnloadAsset(const std::string& name) noexcept
{
    if (!s_Instance.m_Inited)
        return;
}

FT_Library AssetManager::GetFTLibrary() noexcept
{
    return s_Instance.m_FTLibrary;
}

void AssetManager::Shutdown()
{
    if (!s_Instance.m_Inited)
        return;

    for (auto i = s_Instance.m_Table.begin(); i != s_Instance.m_Table.end(); i++)
        i->second.Delete();

    s_Instance.m_Table.clear();
    FT_Done_FreeType(s_Instance.m_FTLibrary);
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
