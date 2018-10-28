#pragma once

#ifdef OBSD_PLATFORM_WINDOWS

extern Obsidian::Application* Obsidian::CreateApplication();

int main(int argc, char** argv) {
	printf("Obsidian Engine\n");
	auto app = Obsidian::CreateApplication();
	app->run();
	delete app;
}

#endif