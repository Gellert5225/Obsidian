#include "obsdpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <GLAD/glad.h>

namespace Obsidian {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: m_WindowHandle(windowHandle) {
		OBSD_CORE_ASSERT(windowHandle, "WindowHandle is null");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		OBSD_CORE_ASSERT(status, "Failed to initialize GLAD");

		OBSD_CORE_INFO("OpenGL Info:");
		OBSD_CORE_INFO("	Vender: {0}", glGetString(GL_VENDOR));
		OBSD_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		OBSD_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}