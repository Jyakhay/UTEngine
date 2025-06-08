#include "GLFWDependency.hpp"

#include <GLFW/glfw3.h>
#include "Debug/DebugLog.hpp"

namespace UTE
{

	bool GLFWDependency::Initialize()
	{
		if (!glfwInit())
		{
			const char* ErrorMessage;
			glfwGetError(&ErrorMessage);

			UTENGINE_LOGFMT("GLFW", ELogSeverity::Error, "Error initializing glfw: \"{}\"", ErrorMessage);
			return false;
		}

		return true;
	}

	bool GLFWDependency::IsRequired()
	{
		return true;
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