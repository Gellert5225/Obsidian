#pragma once

#include "Obsidian/Layer.h"
#include "Obsidian/Events/KeyEvent.h"
#include "Obsidian/Events/MouseEvent.h"
#include "Obsidian/Events/ApplicationEvent.h"

namespace Obsidian {

	class OBSIDIAN_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}