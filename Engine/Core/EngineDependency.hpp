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

		/*Returns if this dependency has been initialized.*/
		bool IsInitialized() const;
		
		virtual std::string GetDependencyName();
		virtual EDependencyLoadGroup GetLoadGroup() = 0;

	private:

		bool mIsInitialized = false;
		friend class DependencyManager;

	};

}