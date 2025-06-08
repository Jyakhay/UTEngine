#include "Executable.hpp"

#include "Platform/FileSystem.hpp"

namespace UTE
{

    void Executable::Initialize(int ArgC, char* ArgV[])
    {
        if(mIsInit)
        {
            return;
        }

        mArgList.reserve(ArgC);
        for(int i = 0; i < ArgC; i++)
        {
            mArgList.push_back(ArgV[i]);
        }

        if(!std::filesystem::exists(FileSystem::GetLogDirectory()))
        {
            std::filesystem::create_directory(FileSystem::GetLogDirectory());
        }
    }

    std::filesystem::path Executable::GetPath()
    {
        return mArgList[0];
    }

}