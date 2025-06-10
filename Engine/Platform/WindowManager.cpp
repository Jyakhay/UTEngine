#include "WindowManager.hpp"

#include "Dependencies/GLFWDependency.hpp"
#include "Debug/DebugLog.hpp"

namespace UTE
{
	UTENGINE_DEFINE_LOG_SOURCE(LogWindowManager, "WindowManager");

	std::weak_ptr<ApplicationWindow> WindowManager::CreateNewWindow(const std::string& ID, uint32_t Width, uint32_t Height, const std::string& Title, EWindowFlagBits WindowFlags)
	{
		if (!DependencyGLFW->IsInitialized())
		{
			UTENGINE_LOG(LogWindowManager, ELogSeverity::Error, "Cannot created window as GLFW is not initialized.");
			return std::weak_ptr<ApplicationWindow>();
		}

		ApplicationWindow* NewWindow = new ApplicationWindow(ID, Width, Height, Title, WindowFlags);
		std::shared_ptr<ApplicationWindow> NewWindowPointer = std::shared_ptr<ApplicationWindow>(NewWindow);
		
		mRegisteredWindows.emplace(ID, NewWindowPointer);
		return std::weak_ptr<ApplicationWindow>(NewWindowPointer);
	}

	std::weak_ptr<ApplicationWindow> WindowManager::GetWindowByID(const std::string& ID)
	{
		auto WindowItr = mRegisteredWindows.find(ID);
		if (WindowItr == mRegisteredWindows.end())
		{
			return std::weak_ptr<ApplicationWindow>();
		}

		return std::weak_ptr<ApplicationWindow>(WindowItr->second);
	}

	bool WindowManager::DestroyWindow(std::weak_ptr<ApplicationWindow>& Window)
	{
		if (Window.expired())
		{
			return false;
		}

		mRegisteredWindows.erase(Window.lock()->GetWindowID());
		return true;
	}

	bool WindowManager::DestroyWindowByID(const std::string& WindowID)
	{
		auto WindowItr = mRegisteredWindows.find(WindowID);
		if (WindowItr == mRegisteredWindows.end())
		{
			return false;
		}

		mRegisteredWindows.erase(WindowItr);
		return true;
	}
}