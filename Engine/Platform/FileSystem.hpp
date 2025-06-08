#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

namespace UTE
{

    class FileSystem
    {

    public:

        static uint32_t GetDirectoryFileCount(const std::filesystem::path& Directory);
        static bool LoadFileIntoBuffer(const std::filesystem::path& Path, std::vector<char>* OutBuffer);

        static std::filesystem::path GetExecutablePath();
        static std::filesystem::path GetExecutableDirectory();
        static std::filesystem::path GetLogDirectory();

    };

}