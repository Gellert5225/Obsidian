#include "obsdpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Obsidian {
	Shader* Shader::Create(const std::string& vertextSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: OBSD_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertextSrc, fragmentSrc);
			default: break;
		}

		OBSD_CORE_ASSERT(false, "Unrecognized RendererAPI");
		return nullptr;
	}
}