#pragma once

#include "Obsidian/Core.h"
#include "Obsidian/Events/Event.h"

#include "Obsidian/Core/Timestep.h"

namespace Obsidian {

	class OBSIDIAN_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}