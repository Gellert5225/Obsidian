#include <Obsidian.h>

#include "imgui.h"

class ExampleLayer : public Obsidian::Layer {
public:
	ExampleLayer()
		:Layer("Example") { }

	void OnUpdate() override {
		// OBSD_INFO("ExampleLayer::Update");

		if (Obsidian::Input::IsKeyPresed(OBSD_KEY_TAB))
			OBSD_TRACE("Tab key pressed");
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Obsidian::Event& event) override {
		// OBSD_TRACE("{0}", event);
		if (event.GetEventType() == Obsidian::EventType::KeyPressed) {
			Obsidian::KeyPressedEvent& e = (Obsidian::KeyPressedEvent&)event;
			OBSD_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
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