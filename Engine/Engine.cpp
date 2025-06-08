#include "Engine.hpp"

#include "Core/DependencyManager.hpp"

namespace UTE
{
	GameEngine* GEngine = new GameEngine();

	bool GameEngine::Initialize()
	{
		if (!DependencyManager::LoadDependencyGroup(EDependencyLoadGroup::Early))
		{
			/*Error Handling*/
			return false;
		}

		return true;
	}

}