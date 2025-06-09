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

		GLFWwindow* GetInternalWindow() const;

	private:

		ApplicationWindow(uint16_t Width, uint16_t Height, const std::string& Title, EWindowFlagBits Flags);
		void EvaluateWindowFlags(EWindowFlagBits Flags);

		GLFWwindow* mInternalWindow = nullptr;

	};

}