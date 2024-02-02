#pragma once

#include <string>
#include <functional>

#include "GEngine/Core.h"

namespace GEngine {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = 1 << 0,
		EventCategoryInput = 1 << 1,
		EventCategoryKeyboard = 1 << 2,
		EventCategoryMouse = 1 << 3,
		EventCategoryMouseButton = 1 << 4
	};

#define EVENT_CLASS_TYPE(type) \
		static EventType GetStaticEventType(){ return EventType::type;} \
		EventType GetEventType() const override { return GetStaticEventType(); } \
		const char* GetEventName() const override {return #type;}
#define EVENT_CLASS_CATEGORY(category) \
		int GetCategoryFlags() const override {return category;}
		

	class WIN_API Event {

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetEventName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetEventName(); }
		
		inline bool IsInCategory(EventCategory category) {
			return category & GetCategoryFlags();
		}

	protected:
		bool m_Handle = false;
	};

	class EvnetDispatcher {
	private:
		Event & m_event;
	public:
		EvnetDispatcher(Event & e):m_event(e){}

		//需要使用方自定义一个用于确认是否handle evnet的函数
		template<typename T>
		using EventFn = std::function<bool(T&)>;
		//这个定义避免了再写 std::function<bool(T&)> 而是写EventFn<T(这里的T是另一个T)
		
		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_event.GetEventType == T::GetStaticEvnetType) {
				m_event.m_Handle = func(*(T*)&m_event);
				//先&变成地址，再转成Tpointer，再读取里面的值
				return true;
			}
			return false;
		}
	};

	inline std::ostream& operator<< (std::ostream & o, const Event & e) {
		//need const error: const T 
		return o << e.ToString();
	}


}