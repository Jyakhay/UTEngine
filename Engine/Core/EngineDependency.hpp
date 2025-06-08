#pragma once

#include <string>
#include "DependencyManager.hpp"

namespace UTE
{

	class EngineDependency
	{

	public:

		virtual bool Initialize() = 0;
		virtual bool IsRequired() = 0;
		
		virtual std::string GetDependencyName();
		virtual EDependencyLoadGroup GetLoadGroup() = 0;

	};

}