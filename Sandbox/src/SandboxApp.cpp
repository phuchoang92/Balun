#include <Balun.h>

#include "imgui/imgui.h"

class ExampleLayer : public Balun::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Balun::Input::IsKeyPressed(BL_KEY_TAB))
			BL_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Welcome to my Game Engine");
		ImGui::End();
	}

	void OnEvent(Balun::Event& event) override
	{
		if (event.GetEventType() == Balun::EventType::KeyPressed)
		{
			Balun::KeyPressedEvent& e = (Balun::KeyPressedEvent&)event;
			if (e.GetKeyCode() == BL_KEY_TAB)
				BL_TRACE("Tab key is pressed (event)!");
			BL_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public Balun::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Balun::Application* Balun::CreateApplication()
{
	return new Sandbox();
}