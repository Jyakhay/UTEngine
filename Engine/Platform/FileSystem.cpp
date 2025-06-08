#include "FileSystem.hpp"

#include "Platform/Executable.hpp"
#include <filesystem>
#include <fstream>
#include <vector>

namespace UTE
{

    uint32_t FileSystem::GetDirectoryFileCount(const std::filesystem::path& Directory)
    {
        uint32_t FileCount = 0;

        for(auto& CurrentDir : std::filesystem::directory_iterator(Directory))
        {
            FileCount++;
        }

        return FileCount;
    }

    bool FileSystem::LoadFileIntoBuffer(const std::filesystem::path& Path, std::vector<char>* OutBuffer)
    {
        if(!std::filesystem::exists(Path))
        {
            return false;
        }

        std::ifstream BinaryStream(Path, std::ios::ate | std::ios::binary);

        if(!BinaryStream.is_open())
        {
            return false;
        }

        size_t BinarySize = BinaryStream.tellg();
        *OutBuffer = std::vector<char>(BinarySize);

        BinaryStream.seekg(0);
        BinaryStream.read(OutBuffer->data(), BinarySize);

        BinaryStream.close();
        return true;
    }

    std::filesystem::path FileSystem::GetExecutablePath()
    {
        return Executable::GetPath();
    }

    std::filesystem::path FileSystem::GetExecutableDirectory()
    {
        return GetExecutablePath().parent_path();
    }

    std::filesystem::path FileSystem::GetLogDirectory()
    {
        return GetExecutableDirectory().append("Logs");
    }

}