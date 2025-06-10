#pragma once

#include <vector>
#include <string>
#include <filesystem>

namespace UTE
{
    
    class Executable
    {

    public:

        static std::filesystem::path GetPath();

    private:

        static void Initialize(int ArgC, char* ArgV[]);

        static inline std::vector<std::string> mArgList = {};
        static inline bool mIsInit = false;

        friend class GameEngine;

    };

}