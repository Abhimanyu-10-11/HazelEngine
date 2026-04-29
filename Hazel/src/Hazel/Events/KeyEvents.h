#pragma once
#include"Event.h"

namespace Hazel
{
	class HAZEL_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() { return m_keyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keyCode):m_keyCode(keyCode){}
		int m_keyCode;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount):KeyEvent(keyCode),m_RepeatCount(repeatCount){}

		inline int GetRepeatCount() { return m_RepeatCount; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent" << m_keyCode << "(" << m_RepeatCount << "Repeat" << ")";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	protected:
		int m_RepeatCount;
	};

	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode):KeyEvent(keyCode){}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent" << m_keyCode;
			return  ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)

		
	};

}


