#include <Obsidian.h>

class ExampleLayer : public Obsidian::Layer {
public:
	ExampleLayer()
		:Layer("Example") { }

	void OnUpdate() override {
		OBSD_INFO("ExampleLayer::Update");
	}

	void OnEvent(Obsidian::Event& event) override {
		OBSD_TRACE("{0}", event);
	}
};

class Sandbox : public Obsidian::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}
};

Obsidian::Application* Obsidian::CreateApplication() {
	return new Sandbox();
}