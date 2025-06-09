#include "DependencyManager.hpp"
#include "EngineDependency.hpp"

#include "Debug/DebugLog.hpp"

namespace UTE
{

    UTENGINE_DEFINE_LOG_SOURCE(LogDependencyManager, "DependencyManager")

    bool DependencyManager::LoadDependencyGroup(EDependencyLoadGroup Group)
    {
        for (auto& CurrentDependency : mRegisteredDependencies[Group])
        {
            std::string DependencyName = CurrentDependency->GetDependencyName();

            UTENGINE_LOGFMT(LogDependencyManager, ELogSeverity::Message, "Initializing dependency \"{}...\"", DependencyName);
            if (!CurrentDependency->Initialize() && CurrentDependency->IsRequired())
            {
                UTENGINE_LOGFMT(LogDependencyManager, ELogSeverity::Error, "Failed to initialize required dependency \"{}\".", DependencyName);
                return false;
            }

            CurrentDependency->mIsInitialized = true;
            UTENGINE_LOGFMT(LogDependencyManager, ELogSeverity::Message, "Dependency \"{}\" initialized.", DependencyName);
        }

        return true;
    }
}