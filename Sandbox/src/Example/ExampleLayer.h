#pragma once

#include"Balun.h"

class ExampleLayer : public Balun::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Balun::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Balun::Event& e) override;
private:
	Balun::ShaderLibrary m_ShaderLibrary;
	Balun::Ref<Balun::Shader> m_Shader;
	Balun::Ref<Balun::VertexArray> m_VertexArray;

	Balun::Ref<Balun::Shader> m_FlatColorShader;
	Balun::Ref<Balun::VertexArray> m_SquareVA;

	Balun::Ref<Balun::Texture2D> m_Texture, m_ChernoLogoTexture;

	Balun::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

