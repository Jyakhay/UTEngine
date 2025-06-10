#pragma once

#include <cstdint>
#include <string>

struct GLFWwindow;

namespace UTE
{
	namespace EWindowFlags
	{
		enum EType
		{
			WinFlag_None = 0 << 0,
			WinFlag_Maximized = 1 << 0
		};
	}

	typedef int EWindowFlagBits;

	class ApplicationWindow
	{

	public:

		bool UTENGINE_API IsPendingClose() const;

		std::string GetWindowID() const;
		GLFWwindow* GetInternalWindow() const;

	private:

		ApplicationWindow(const std::string& ID, uint16_t Width, uint16_t Height, const std::string& Title, EWindowFlagBits Flags);
		void EvaluateWindowFlags(EWindowFlagBits Flags);

		GLFWwindow* mInternalWindow = nullptr;
		std::string mWindowID = "";
		friend class WindowManager;

	};

}