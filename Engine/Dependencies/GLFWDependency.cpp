#include "GLFWDependency.hpp"

#include <GLFW/glfw3.h>
#include "Debug/DebugLog.hpp"

namespace UTE
{

	UTENGINE_DEFINE_LOG_SOURCE(LogGLFW, "GLFW");

	bool GLFWDependency::Initialize()
	{
		if (!glfwInit())
		{
			const char* ErrorMessage;
			glfwGetError(&ErrorMessage);

			UTENGINE_LOGFMT(LogGLFW, ELogSeverity::Error, "Error initializing glfw: \"{}\"", ErrorMessage);
			return false;
		}

		return true;
	}

	bool GLFWDependency::IsRequired()
	{
		return true;
	}

	void GLFWDependency::UpdateEvents() const
	{
		glfwPollEvents();
	}

	std::string GLFWDependency::GetDependencyName()
	{
		return "GLFW";
	}

	EDependencyLoadGroup GLFWDependency::GetLoadGroup()
	{
		return EDependencyLoadGroup::Early;
	}

}