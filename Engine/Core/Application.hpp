#pragma once

#include "Platform/WindowManager.hpp"
#include <memory>

namespace UTE
{

	class Application
	{

	public:

		virtual UTENGINE_API void Initialize();
		virtual UTENGINE_API void Update();
		virtual UTENGINE_API void Shutdown();

		/*Returns the application's window manager.*/
		UTENGINE_API WindowManager* GetWindowManager() const;

		/*Returns if the application is still running, and therefore if the engine should shutdown.*/
		virtual UTENGINE_API bool IsRunning() const;

	protected:

		UTENGINE_API Application();
		virtual UTENGINE_API ~Application();

	private:

		std::unique_ptr<WindowManager> mWindowManager = nullptr;
		friend class GameEngine;

	};

}