#include "SandboxApp.hpp"

#include "Rendering/RenderManager.hpp"
#include "Rendering/OpenGL/OGLRenderingAPI.hpp"

void SandboxApp::Initialize()
{
	UTE::Application::Initialize();

	MainWindow = GetWindowManager()->CreateNewWindow("SandboxWindow", 640, 460, "Sandbox", 0);

	UTE::RenderManager::InitializeAPI<UTE::OGLRenderingAPI>();
	UTE::RenderManager::GetRenderingAPI()->InitializeAPI(MainWindow);

}

void SandboxApp::Update()
{
	UTE::Application::Update();

	if (!MainWindow.expired())
	{
		auto WindowRef = MainWindow.lock();

		if (WindowRef->IsPendingClose())
		{
			GetWindowManager()->DestroyWindow(MainWindow);
		}
		else
		{
			UTE::RenderManager::GetRenderingAPI()->RefreshDisplay();
		}
	}
}

void SandboxApp::Shutdown()
{
	UTE::Application::Shutdown();
}

bool SandboxApp::IsRunning() const
{
	return !MainWindow.expired();
}