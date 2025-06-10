#include "Engine.hpp"
#include "SandboxApp.hpp"

int main(int ArgC, char* ArgV[])
{
	if (UTE::GEngine->Initialize(ArgC, ArgV))
	{
		SandboxApp* TestApp = UTE::GEngine->CreateApplication<SandboxApp>();

		while (UTE::GEngine->IsRunning())
		{
			UTE::GEngine->Update();
		}
	}
	else
	{
		return -1;
	}

	UTE::GEngine->Shutdown();
	return 0;
}