#include "obsdpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Obsidian {

	Renderer::SceneData* Renderer::m_SceneData = new SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera) {
		m_SceneData->VPMatrix = camera.GetVPMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4 transform) {
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->VPMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}