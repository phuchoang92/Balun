#include <Balun.h>

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

	void OnEvent(Balun::Event& event) override
	{
		if (event.GetEventType() == Balun::EventType::KeyPressed)
		{
			Balun::KeyPressedEvent& e = (Balun::KeyPressedEvent&) event;
			BL_TRACE("{0}", (char)e.GetKeyCode());
			/*if (e.GetKeyCode() == BL_KEY_TAB)
			{
				BL_TRACE("Tab key is pressed (event)!");
				BL_TRACE("{0}", (char)e.GetKeyCode());
			}*/
		}
	}

private:

};

class Sandox : public Balun::Application 
{
public:
	Sandox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Balun::ImGuiLayer());
	}
	
	~Sandox() {

	}
};

Balun::Application* Balun::CreateApplication() {
	return new Sandox();
}