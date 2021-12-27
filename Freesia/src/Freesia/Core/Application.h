//
// Created by Htrap19 on 12/1/21.
//

#ifndef FREESIA_APPLICATION_H
#define FREESIA_APPLICATION_H

#include "Freesia/Core/Window.h"
#include "Freesia/Core/LayerStack.h"
#include "Freesia/Events/WindowEvent.h"
#include "Freesia/ImGui/ImGuiLayer.h"

namespace Freesia
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void OnEvent(Event& e);
        void Run();

        inline void PushLayer(Layer* layer) { layer->OnAttach(); m_LayerStack.PushLayer(layer); }
        inline void PushOverlay(Layer* layer) { layer->OnAttach(); m_LayerStack.PushOverlay(layer); }

        static inline Application& Get() { return *s_Instance; }
        inline Window& GetWindow() const { return *m_Window; }
        inline ImGuiLayer& GetImGuiLayer() const { return *m_ImGuiLayer; }

        inline void Close() { m_Running = false; }

    private:
        bool OnWindowClose(WindowClosedEvent& e);
        bool OnWindowResize(WindowResizedEvent& e);

    private:
        Scope<Window> m_Window;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;
        ImGuiLayer* m_ImGuiLayer;

        // Single-Ton
        static Application* s_Instance;
    };

    Application* CreateApplication();
}

#endif //FREESIA_APPLICATION_H
