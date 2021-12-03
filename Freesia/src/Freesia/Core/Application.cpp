//
// Created by Htrap19 on 12/1/21.
//

#include "Application.h"

namespace Freesia
{
    Application::Application()
    {
        m_Window = Window::Create();
        m_Window->SetEventCallback(FS_BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application()
    {}

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowClosedEvent>(FS_BIND_EVENT_FN(Application::OnWindowClose));
    }

    void Application::Run()
    {
        while(m_Running)
        {
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowClosedEvent &e)
    {
        m_Running = false;
        return false;
    }
}