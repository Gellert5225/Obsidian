#include "obsdpch.h"

#include "Texture.h"

#include "Renderer.h"

#include "Obsidian/Core.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include <string>

namespace Obsidian {
	Ref<Texture2D> Texture2D::Create(const std::string & path) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: OBSD_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
			default: break;
		}

		OBSD_CORE_ASSERT(false, "Unrecognized RendererAPI");
		return nullptr;
	}
}