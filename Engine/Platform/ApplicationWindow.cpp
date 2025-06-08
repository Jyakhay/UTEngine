#include "ApplicationWindow.hpp"

namespace UTE
{
	GLFWwindow* ApplicationWindow::GetInternalWindow() const
	{
		return mInternalWindow;
	}
}