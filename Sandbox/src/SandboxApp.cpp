#include <Balun.h>
#include <Balun/Core/EntryPoint.h>

#include "Example/ExampleLayer.h"
#include "Game/GameLayer.h"
#include "Sandbox2D.h"

class Sandbox : public Balun::Application
{
public:
	Sandbox()
	{
		//PushLayer(new GameLayer());
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Balun::Application* Balun::CreateApplication()
{
	return new Sandbox();
}