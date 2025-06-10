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

		/*Creates a new window and registers it under the specified ID.*/
		std::weak_ptr<ApplicationWindow> UTENGINE_API CreateNewWindow(const std::string& ID, uint32_t Width, uint32_t Height, const std::string& Title, EWindowFlagBits WindowFlags);

		/*Retrieves a registered window by the specified ID, returns expired weak_ptr if window using ID wasn't found.*/
		std::weak_ptr<ApplicationWindow> UTENGINE_API GetWindowByID(const std::string& ID);

		/*Destroys and unregisters the specified window.*/
		bool UTENGINE_API DestroyWindow(std::weak_ptr<ApplicationWindow>& Window);

		/*Destroys and unregistered the window assigned the specified ID.*/
		bool UTENGINE_API DestroyWindowByID(const std::string& WindowID);


	private:

		std::unordered_map<std::string /*WindowID*/, std::shared_ptr<ApplicationWindow>> mRegisteredWindows;

	};

}