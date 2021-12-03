//
// Created by Htrap19 on 12/3/21.
//

#ifndef FREESIA_WINDOWEVENT_H
#define FREESIA_WINDOWEVENT_H

#include "Freesia/Events/Event.h"

namespace Freesia
{
    class WindowResizedEvent : public Event
    {
    public:
        WindowResizedEvent(uint32_t width, uint32_t height)
            : m_Width(width), m_Height(height)
        {}

        inline uint32_t GetWidth() const { return m_Width; }
        inline uint32_t GetHeight() const { return m_Height; }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)

    private:
        uint32_t m_Width, m_Height;
    };

    class WindowClosedEvent : public Event
    {
    public:
        WindowClosedEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };
}

#endif //FREESIA_WINDOWEVENT_H
