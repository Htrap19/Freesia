//
// Created by Htrap19 on 12/3/21.
//

#ifndef FREESIA_MOUSEEVENT_H
#define FREESIA_MOUSEEVENT_H

#include "Freesia/Events/Event.h"
#include "Freesia/Core/MouseCodes.h"

namespace Freesia
{
    class MouseButtonEvent : public Event
    {
    public:
        inline MouseCode GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

    protected:
        explicit MouseButtonEvent(const MouseCode button)
            : m_Button(button)
        {}

    protected:
        MouseCode m_Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        explicit MouseButtonPressedEvent(const MouseCode button)
            : MouseButtonEvent(button)
        {}

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        explicit MouseButtonReleasedEvent(const MouseCode button)
                : MouseButtonEvent(button)
        {}

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
            : m_XPos(x), m_YPos(y)
        {}

        inline float GetMouseX() const { return m_XPos; }
        inline float GetMouseY() const { return m_YPos; }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse);

    private:
        float m_XPos, m_YPos;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
                : m_XOffset(xOffset), m_YOffset(yOffset)
        {}

        inline float GetXOffset() const { return m_XOffset; }
        inline float GetYOffset() const { return m_YOffset; }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse);

    private:
        float m_XOffset, m_YOffset;
    };
}

#endif //FREESIA_MOUSEEVENT_H
