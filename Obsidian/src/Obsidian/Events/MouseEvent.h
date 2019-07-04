#pragma once

#include "Event.h"

namespace Obsidian {

	class OBSIDIAN_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override {
			std::stringstream out;
			out << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return out.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	class OBSIDIAN_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override {
			std::stringstream out;
			out << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return out.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};

	class OBSIDIAN_API MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return m_Button; }
		
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {
		}
		int m_Button;
	};

	class OBSIDIAN_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {
		}

		std::string ToString() const override {
			std::stringstream out;
			out << "MouseButtonPressedEvent: " << m_Button;
			return out.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class OBSIDIAN_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {
		}

		std::string ToString() const override {
			std::stringstream out;
			out << "MouseButtonReleasedEvent: " << m_Button;
			return out.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}