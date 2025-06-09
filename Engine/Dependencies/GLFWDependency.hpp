#pragma once

#include "Core/EngineDependency.hpp"

namespace UTE
{

	class GLFWDependency : public EngineDependency
	{

	public:

		virtual bool Initialize() override;
		virtual bool IsRequired() override;

		void UpdateEvents() const;

		virtual std::string GetDependencyName() override;
		virtual EDependencyLoadGroup GetLoadGroup() override;

	};

	REGISTER_UTENGINE_DEPENDENCY(GLFWDependency, DependencyGLFW)

}