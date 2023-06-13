#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckboardTexture = Balun::Texture2D::Create("assets/textures/Checkerboard.png");

}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Balun::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Balun::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Balun::RenderCommand::Clear();

	Balun::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Balun::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f,0.2f,0.3f,1.0f});
	Balun::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f,0.3f,0.8f,1.0f});
	Balun::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, m_CheckboardTexture);
	Balun::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Balun::Event& event)
{
	m_CameraController.OnEvent(event);
}
