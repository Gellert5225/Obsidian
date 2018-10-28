#include <Obsidian.h>

class Sandbox : public Obsidian::Application {

public:
	Sandbox() {}
	~Sandbox() {}
};

Obsidian::Application* Obsidian::CreateApplication() {
	return new Sandbox();
}