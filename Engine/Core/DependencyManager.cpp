#include "DependencyManager.hpp"
#include "EngineDependency.hpp"

#include "Debug/DebugLog.hpp"

namespace UTE
{
    bool DependencyManager::LoadDependencyGroup(EDependencyLoadGroup Group)
    {
        for (auto& CurrentDependency : mRegisteredDependencies[Group])
        {
            UTENGINE_LOGFMT("DependencyManager", ELogSeverity::Message, "Initializing dependency \"{}...\"", CurrentDependency->GetDependencyName());
            if (!CurrentDependency->Initialize() && CurrentDependency->IsRequired())
            {
                UTENGINE_LOGFMT("DependencyManager", ELogSeverity::Error, "Failed to initialize required dependency \"{}\".", CurrentDependency->GetDependencyName());
                return false;
            }
            UTENGINE_LOGFMT("DependencyManager", ELogSeverity::Message, "Dependency \"{}\" initialized.", CurrentDependency->GetDependencyName());
        }

        return true;
    }
}