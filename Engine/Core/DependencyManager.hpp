#pragma once

#include <unordered_map>
#include <vector>
#include <string>

namespace UTE
{

	class EngineDependency;

	enum class EDependencyLoadGroup
	{
		Early,
		PostGraphics
	};

	class DependencyManager
	{

	public:

		template<class T>
		static void RegisterDependency()
		{
			T* NewDependency = new T();
			mRegisteredDependencies[NewDependency->GetLoadGroup()].push_back(NewDependency);
		}

		static bool LoadDependencyGroup(EDependencyLoadGroup Group);

	private:

		static inline std::unordered_map<EDependencyLoadGroup, std::vector<EngineDependency*>> mRegisteredDependencies;

	};

	template<class T>
	struct StaticDependencyRegister
	{
		StaticDependencyRegister()
		{
			DependencyManager::RegisterDependency<T>();
		}
	};

	#define REGISTER_UTENGINE_DEPENDENCY(DependencyType, DependencyName) static inline StaticDependencyRegister<DependencyType> DependencyName = StaticDependencyRegister<DependencyType>();
}