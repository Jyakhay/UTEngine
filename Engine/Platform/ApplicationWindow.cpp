#include "ApplicationWindow.hpp"

#include <GLFW/glfw3.h>

namespace UTE
{
	GLFWwindow* ApplicationWindow::GetInternalWindow() const
	{
		return mInternalWindow;
	}

	ApplicationWindow::ApplicationWindow(uint16_t Width, uint16_t Height, const std::string& Title, EWindowFlagBits Flags)
	{
		glfwDefaultWindowHints();
		/*Todo - Rendering API should set it's required flags.*/
		EvaluateWindowFlags(Flags);

		mInternalWindow = glfwCreateWindow(Width, Height, Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(mInternalWindow);
	}

	void ApplicationWindow::EvaluateWindowFlags(EWindowFlagBits Flags)
	{
		glfwWindowHint(GLFW_MAXIMIZED, Flags & EWindowFlags::WinFlag_Maximized);
	}
}
