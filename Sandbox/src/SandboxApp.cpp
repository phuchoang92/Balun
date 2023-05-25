#include <Balun.h>

#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "Platform/OpenGL/OpenGLShader.h"
#include <Balun/OrthographicCameraController.h>

class ExampleLayer : public Balun::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray.reset(Balun::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Balun::Ref<Balun::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Balun::VertexBuffer::Create(vertices, sizeof(vertices)));

		Balun::BufferLayout layout = {
			{ Balun::ShaderDataType::Float3, "a_Position" },
			{ Balun::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Balun::Ref<Balun::IndexBuffer> indexBuffer;
		indexBuffer.reset(Balun::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(Balun::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Balun::Ref<Balun::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Balun::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVertexBuffer->SetLayout({
			{ Balun::ShaderDataType::Float3, "a_Position" },
			{ Balun::ShaderDataType::Float2, "a_TexCoord" }
		});

		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Balun::Ref<Balun::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Balun::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Balun::Shader::Create("VertexColorTriangle", vertexSrc, fragmentSrc);

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()

			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string  blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Balun::Shader::Create("VertexColorSquare", blueShaderVertexSrc, blueShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Balun::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Balun::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Balun::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Balun::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Balun::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		Balun::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Balun::RenderCommand::Clear();

		Balun::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Balun::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Balun::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Balun::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Balun::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//Balun::Renderer::Submit(m_Shader, m_VertexArray);
		m_LogoTexture->Bind();
		Balun::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		Balun::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Balun::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

	bool OnKeyPressedEvent(Balun::KeyPressedEvent& event)
	{
	}
private:

	Balun::ShaderLibrary m_ShaderLibrary;
	Balun::Ref<Balun::VertexArray> m_VertexArray;
	Balun::Ref<Balun::Shader> m_Shader;

	Balun::Ref<Balun::Shader> m_FlatColorShader;
	Balun::Ref<Balun::VertexArray> m_SquareVertexArray;
	Balun::Ref<Balun::Texture2D> m_Texture, m_LogoTexture;

	Balun::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
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