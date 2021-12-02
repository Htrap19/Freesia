//
// Created by Htrap19 on 12/1/21.
//

#ifndef FREESIA_WINDOW_H
#define FREESIA_WINDOW_H

#include <string>
#include <utility>
#include <Freesia/Core/Core.h>

namespace Freesia
{
    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        explicit WindowProps(std::string title = "Freesia", uint32_t width = 720, uint32_t height = 480)
            : Title(std::move(title)), Width(width), Height(height) {}
    };

    class Window
    {
    public:
        virtual ~Window() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void OnUpdate() = 0;

        static Scope<Window> Create(const WindowProps& props = WindowProps());
    };
}

#endif //FREESIA_WINDOW_H
