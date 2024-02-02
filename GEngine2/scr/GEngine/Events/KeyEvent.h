#pragma once
#include "Event.h"
#include <sstream>

namespace GEngine {
	
	class WIN_API KeyEvent: public Event {

	protected:
		int m_keycode;

		KeyEvent(int keycode): m_keycode(keycode){}

	public:
		inline int GetKeycode()const { return m_keycode; }
		
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};

	class WIN_API KeyPressEvented : public KeyEvent {
	private:
		int m_keyReapt;
	public:
		KeyPressEvented(int keycode, int keyReapt): KeyEvent(keycode), m_keyReapt(keyReapt){}
		inline int GetKeyReapt() const { return m_keyReapt; }

		std::string ToString() {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keycode << " & " << m_keyReapt << "Reapted";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class WIN_API KeyReleasedEvent: public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode): KeyEvent(keycode){}

		std::string ToString() {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}