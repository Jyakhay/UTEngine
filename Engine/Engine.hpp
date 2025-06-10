#pragma once

#include "Core/Application.hpp"
#include <memory>

namespace UTE
{

	class GameEngine
	{

	public:

		bool UTENGINE_API Initialize(int ArgC, char* ArgV[]);
		
		template<class T>
		T* CreateApplication()
		{
			T* NewApplication = new T();
			mApplication = NewApplication;
			NewApplication->Initialize();

			return NewApplication;
		}

		template<class T>
		T* GetApplication()
		{
			return static_cast<T*>(mApplication);
		}

		Application* GetApplication()
		{
			return mApplication;
		}

		void UTENGINE_API Update();
		void UTENGINE_API Shutdown();

		bool UTENGINE_API IsRunning();

	private:

		Application* mApplication = nullptr;

	};

	extern UTENGINE_API GameEngine* GEngine;

}