#pragma once
#include <sstream>
#include "Event.h"

namespace GEngine {

	class WIN_API MouseMovedEvent : public Event {
	private:
		float m_x;
		float m_y;
	public:
		MouseMovedEvent(float x, float y) : m_x(x), m_y(y) {}

		inline float GetX() const { return m_x; }
		inline float GetY() const { return m_y; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent " << m_x << ", " << m_y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	};

	class WIN_API MouseButtonEvent : public Event {
	protected: 
		int m_mouseButton;

		MouseButtonEvent(int button):m_mouseButton(button){}

	public:
		inline int GetMouseButton() const { return m_mouseButton; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	};

	class WIN_API MouseButtonPressedEvent : public MouseButtonEvent 
	{
	public:
		MouseButtonPressedEvent(int button): MouseButtonEvent(button){}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_mouseButton;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class WIN_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button): MouseButtonEvent(button){}
		
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_mouseButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

	class WIN_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};
}