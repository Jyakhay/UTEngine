#include "Application.hpp"

namespace UTE
{

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Initialize()
	{
		mWindowManager = std::make_unique<WindowManager>();
	}

	void Application::Update()
	{
	}

	void Application::Shutdown()
	{
	}

	WindowManager* Application::GetWindowManager() const
	{
		return mWindowManager.get();
	}

	bool Application::IsRunning() const
	{
		return true;
	}

}