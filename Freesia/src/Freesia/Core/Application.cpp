//
// Created by Htrap19 on 12/1/21.
//

#include "Application.h"

namespace Freesia
{
    Application::Application()
    {
        m_Window = Window::Create();
    }

    Application::~Application()
    {}

    void Application::Run()
    {
        while(m_Running)
        {
            m_Window->OnUpdate();
        }
    }
}