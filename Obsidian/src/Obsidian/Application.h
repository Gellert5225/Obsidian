#pragma once

#include "Core.h"
#include "Window.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Obsidian/LayerStack.h"

#include "Obsidian/ImGui/ImGuiLayer.h"

#include "Obsidian/Renderer/Shader.h"

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
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<ImGuiLayer> m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		bool OnWindowClosed(WindowCloseEvent& e);
	};
	// To be defined in client
	Application* CreateApplication();

}
