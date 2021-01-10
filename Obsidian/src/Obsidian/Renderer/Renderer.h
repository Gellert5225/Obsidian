#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Obsidian {
	
	class Renderer {
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const Ref<VertexArray>& vertexArray, 
							const Ref<Shader>& shader, 
							const glm::mat4 transform = glm::mat4(1.0f));

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 VPMatrix;
		};

		static SceneData* m_SceneData;
	};
}