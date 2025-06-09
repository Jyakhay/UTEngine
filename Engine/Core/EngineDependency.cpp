#include "EngineDependency.hpp"

namespace UTE
{
	bool EngineDependency::IsInitialized() const
	{
		return mIsInitialized;
	}

	std::string EngineDependency::GetDependencyName()
	{
		return "UnnamedDependency";
	}
}