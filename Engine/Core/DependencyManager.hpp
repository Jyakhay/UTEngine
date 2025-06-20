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

		/*Registers a dependency, queuing it for initialization.*/
		template<class T>
		static T* RegisterDependency()
		{
			T* NewDependency = new T();
			mRegisteredDependencies[NewDependency->GetLoadGroup()].push_back(NewDependency);

			return NewDependency;
		}

		/*Initializes all dependencies set to load at the specified load group.*/
		static bool LoadDependencyGroup(EDependencyLoadGroup Group);

	private:

		static inline std::unordered_map<EDependencyLoadGroup, std::vector<EngineDependency*>> mRegisteredDependencies;

	};

	template<class T>
	struct StaticDependencyRegister
	{
		StaticDependencyRegister()
		{
			Instance = DependencyManager::RegisterDependency<T>();
		}

		T* Instance = nullptr;
	};

	#define REGISTER_UTENGINE_DEPENDENCY(DependencyType, DependencyName) \
	inline StaticDependencyRegister<DependencyType> DepReg = StaticDependencyRegister<DependencyType>();\
	inline DependencyType* DependencyName = DepReg.Instance;
	
	
}