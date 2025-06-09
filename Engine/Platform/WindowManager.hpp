#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "ApplicationWindow.hpp"

namespace UTE
{

	class WindowManager
	{

	public:

		std::weak_ptr<ApplicationWindow> UTENGINE_API CreateNewWindow(const std::string& ID, uint32_t Width, uint32_t Height, const std::string& Title, EWindowFlagBits WindowFlags);

	private:

		std::unordered_map<std::string /*WindowID*/, std::shared_ptr<ApplicationWindow>> mRegisteredWindows;

	};

}