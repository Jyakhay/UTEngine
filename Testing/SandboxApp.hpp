#pragma once

#include "Core/Application.hpp"

class SandboxApp : public UTE::Application
{

public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Shutdown() override;

	virtual bool IsRunning() const override;

private:

	std::weak_ptr<UTE::ApplicationWindow> MainWindow;

};