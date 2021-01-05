#include <Obsidian.h>

#include "imgui.h"

class ExampleLayer : public Obsidian::Layer {
public:
	ExampleLayer()
		:Layer("Example"),
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_CameraPosition(0.0f) {

		m_VertexArray.reset(Obsidian::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Obsidian::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Obsidian::VertexBuffer::Create(vertices, sizeof(vertices)));

		Obsidian::BufferLayout layout = {
			{Obsidian::ShaderDataType::Float3, "position"},
			{Obsidian::ShaderDataType::Float4, "color"}
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Obsidian::IndexBuffer> indexBuffer;
		indexBuffer.reset(Obsidian::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Obsidian::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Obsidian::VertexBuffer> squareVB;
		squareVB.reset((Obsidian::VertexBuffer::Create(squareVertices, sizeof(squareVertices))));

		squareVB->SetLayout({
			{Obsidian::ShaderDataType::Float3, "position"}
			});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Obsidian::IndexBuffer> squareIB;
		squareIB.reset((Obsidian::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 position;
			layout(location = 1) in vec4 color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_position;
			out vec4 v_color;
			
			void main() {
				v_position = position;
				v_color = color;
				gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
			}
		
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
				
			in vec3 v_position;
			in vec4 v_color;

			void main() {
				color = v_color;
			}
		
		)";

		m_Shader.reset(new Obsidian::Shader(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_position;
			
			void main() {
				v_position = position;
				gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
			}
		
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
				
			in vec3 v_position;

			void main() {
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		
		)";

		m_Shader2.reset(new Obsidian::Shader(vertexSrc2, fragmentSrc2));
	}

	void OnUpdate(Obsidian::Timestep ts) override {
		//OBSD_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		if (Obsidian::Input::IsKeyPressed(OBSD_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Obsidian::Input::IsKeyPressed(OBSD_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Obsidian::Input::IsKeyPressed(OBSD_KEY_UP)) 
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Obsidian::Input::IsKeyPressed(OBSD_KEY_DOWN)) 
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Obsidian::Input::IsKeyPressed(OBSD_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Obsidian::Input::IsKeyPressed(OBSD_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Obsidian::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Obsidian::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Obsidian::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				glm::vec3 position(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
				Obsidian::Renderer::Submit(m_SquareVA, m_Shader2, transform);
			}
		}
		Obsidian::Renderer::Submit(m_VertexArray, m_Shader);

		Obsidian::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
	}

	void OnEvent(Obsidian::Event& event) override {
	}

private:
	std::shared_ptr<Obsidian::Shader> m_Shader;
	std::shared_ptr<Obsidian::Shader> m_Shader2;
	std::shared_ptr<Obsidian::VertexArray> m_VertexArray;
	std::shared_ptr<Obsidian::VertexArray> m_SquareVA;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 90.0f;

	Obsidian::OrthographicCamera m_Camera;
};

class Sandbox : public Obsidian::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Obsidian::ImGuiLayer());
	}
	~Sandbox() {}
};

Obsidian::Application* Obsidian::CreateApplication() {
	return new Sandbox();
}