//
// Created by Htrap19 on 12/1/21.
//

#include "Application.h"

#include <GLFW/glfw3.h>

#include "Freesia/Core/Assert.h"
#include "Freesia/Renderer/Renderer.h"

namespace Freesia
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        FS_CORE_ASSERT(!s_Instance, "Application instance already exists!");
        s_Instance = this;

        m_Window = Window::Create();
        m_Window->SetEventCallback(FS_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer;
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
        Renderer::Shutdown();
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowClosedEvent>(FS_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizedEvent>(FS_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++)
        {
            (*it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::Run()
    {
        while(m_Running)
        {
            auto time = (float)glfwGetTime();
            TimeStep timeStep = time - m_LastFrameTime;
            m_LastFrameTime = timeStep;

            if (!m_Minimized)
            {
                for (Layer* layer : m_LayerStack)
                    layer->OnUpdate(m_LastFrameTime);
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowClosedEvent &e)
    {
        m_Running = false;
        return false;
    }

    bool Application::OnWindowResize(WindowResizedEvent &e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        return false;
    }
}