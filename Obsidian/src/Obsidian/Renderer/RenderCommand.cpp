#include "obsdpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Obsidian {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}