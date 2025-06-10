#include "Engine.hpp"

#include "Core/DependencyManager.hpp"
#include "Platform/Executable.hpp"

#include "Dependencies/GLFWDependency.hpp"
#include "Debug/DebugLog.hpp"

namespace UTE
{

	UTENGINE_DEFINE_LOG_SOURCE(LogEngine, "UTEngine")

	GameEngine* GEngine = new GameEngine();

	bool GameEngine::Initialize(int ArgC, char* ArgV[])
	{
		Executable::Initialize(ArgC, ArgV);
		DebugLogger::BeginLogSession();

		if (!DependencyManager::LoadDependencyGroup(EDependencyLoadGroup::Early))
		{
			UTENGINE_LOG(LogEngine, ELogSeverity::Error, "Failed to initialize required dependencies.");
			DebugLogger::EndLogSession();

			return false;
		}

		return true;
	}

	void GameEngine::Update()
	{
		DependencyGLFW->UpdateEvents();

		if (mApplication)
		{
			mApplication->Update();
		}
	}

	void GameEngine::Shutdown()
	{
		if (mApplication)
		{
			mApplication->Shutdown();

			delete mApplication;
			mApplication = nullptr;
		}

		DebugLogger::EndLogSession();
	}

	bool GameEngine::IsRunning()
	{
		return mApplication ? mApplication->IsRunning() : true;
	}

}