#pragma once

#include "Core.h"

#include "Window.h"
#include "Balun/Core/LayerStack.h"
#include "Balun/Events/Event.h"
#include "Balun/ImGui/ImGuiLayer.h"
#include "Balun/Events/ApplicationEvent.h"
#include "Balun/Core/Timestep.h"
#include "Balun/Renderer/Shader.h"
#include "Balun/Renderer/Buffer.h"
#include "Balun/Renderer/VertexArray.h"
#include "Balun/Renderer/OrthographicCamera.h"

namespace Balun {

	class BALUN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}