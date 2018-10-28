#pragma once

#include "Core.h"

namespace Obsidian {

	class OBSIDIAN_API Application {
	public:
		Application();
		virtual ~Application();
		void run();
	};
	// To be defined in client
	Application* CreateApplication();
}
