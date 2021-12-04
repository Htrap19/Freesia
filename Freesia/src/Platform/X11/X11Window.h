//
// Created by Htrap19 on 12/1/21.
//

#ifndef FREESIA_X11WINDOW_H
#define FREESIA_X11WINDOW_H

#include "Freesia/Core/Window.h"
#include "Freesia/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Freesia
{
    class X11Window : public Window
    {
    public:
        explicit X11Window(const WindowProps& props);
        ~X11Window() override;

        inline uint32_t GetWidth() const override { return m_Data.Width; }
        inline uint32_t GetHeight() const override { return m_Data.Height; }

        void OnUpdate() override;

        inline void SetEventCallback(const EventCallbackFn &fn) override { m_Data.EventCallback = fn; }
        inline void* GetNativeWindow() const override { return m_Window; }

    private:
        void Init(const WindowProps& props);
        void Shutdown();

    private:
        GLFWwindow* m_Window;
        Scope<GraphicsContext> m_Context;

        struct WindowData
        {
            std::string Title;
            uint32_t Width, Height;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}

#endif //FREESIA_X11WINDOW_H
