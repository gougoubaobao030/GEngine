#pragma once
#include "Event.h"
#include <sstream>
namespace GEngine {

	class WIN_API WindowResizeEvnet : public Event {
	private:
		unsigned int m_width;
		unsigned int m_height;
	public:
		WindowResizeEvnet(unsigned int width, unsigned int height) :
			m_width(width), m_height(height) {

		}

		inline unsigned int GetWidth() { return m_width; }
		inline unsigned int GetHeight() { return m_height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << "," << m_height;
			//string 不能直接 + m_width, 需要to_stirng(m_width); 所以这里使用ss比较方便。
			return ss.str();

		}

		EVENT_CLASS_TYPE(WindowResize)
		//上面这个return 要char* 而不是string的理由是 return 的是 raw的 "WindowResize";
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

	class WIN_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {};

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WIN_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WIN_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WIN_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}