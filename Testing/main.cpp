#include "Engine.hpp"

#include "Platform/WindowManager.hpp"

int main()
{
	if (!UTE::GEngine->Initialize())
	{
		return -1;
	}

	UTE::WindowManager Manager;
	Manager.CreateNewWindow("GameWindow", 640, 480, "Sandbox", 0);

	while (true)
	{
		UTE::GEngine->Update();
	}

	return 0;
}