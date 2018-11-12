#pragma once

#ifdef OBSD_PLATFORM_WINDOWS

extern Obsidian::Application* Obsidian::CreateApplication();

int main(int argc, char** argv) {
	Obsidian::Log::Init();
	OBSD_CORE_WARN("Initialized Log!");
	OBSD_INFO("Hello!");

	auto app = Obsidian::CreateApplication();
	app->run();
	delete app;
}

#endif