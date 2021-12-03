//
// Created by Htrap19 on 12/3/21.
//

#ifndef FREESIA_KEYEVENT_H
#define FREESIA_KEYEVENT_H

#include "Freesia/Events/Event.h"
#include "Freesia/Core/KeyCodes.h"

namespace Freesia
{
    class KeyEvent : public Event
    {
    public:
        inline KeyCode GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

    protected:
        explicit KeyEvent(const KeyCode keyCode)
            : m_KeyCode(keyCode)
        {}

    protected:
        KeyCode m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(const KeyCode key, uint16_t repeatCount)
            : KeyEvent(key), m_RepeatCount(repeatCount)
        {}

        inline uint16_t GetRepeatCount() const { return m_RepeatCount; }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        uint16_t m_RepeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(const KeyCode key)
            : KeyEvent(key)
        {}

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        explicit KeyTypedEvent(const KeyCode key)
            : KeyEvent(key)
        {}

        EVENT_CLASS_TYPE(KeyTyped)
    };
}

#endif //FREESIA_KEYEVENT_H
