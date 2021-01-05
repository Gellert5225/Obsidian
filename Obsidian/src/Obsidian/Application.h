#pragma once

#include "Core.h"
#include "Window.h"

#include "Obsidian/Core/Timestep.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Obsidian/LayerStack.h"

#include "Obsidian/ImGui/ImGuiLayer.h"

#include "Obsidian/Renderer/Shader.h"
#include "Obsidian/Renderer/Buffer.h"
#include "Obsidian/Renderer/VertexArray.h"
#include "Obsidian/Renderer/OrthographicCamera.h"

namespace Obsidian {

	class OBSIDIAN_API Application {
	public:
		Application();
		virtual ~Application();
		void run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		static Application* s_Instance;

		bool OnWindowClosed(WindowCloseEvent& e);
		bool m_Running = true;

		LayerStack m_LayerStack;

		std::unique_ptr<Window> m_Window;
		std::unique_ptr<ImGuiLayer> m_ImGuiLayer;

		float m_LastFrameTime = 0.0f;
	};
	// To be defined in client
	Application* CreateApplication();

}
