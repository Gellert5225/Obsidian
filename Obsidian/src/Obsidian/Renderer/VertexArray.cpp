#include "obsdpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Obsidian {
	VertexArray * VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: OBSD_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		default: break;
		}

		OBSD_CORE_ASSERT(false, "Unrecognized RendererAPI");
		return nullptr;
	}
}