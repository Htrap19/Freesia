//
// Created by Htrap19 on 12/1/21.
//

#include "X11Window.h"

#include "GLFW/glfw3.h"
#include <iostream>

namespace Freesia
{
    static bool s_GLFWInitialized = false;

    X11Window::X11Window(const Freesia::WindowProps &props)
    {
        Init(props);
    }

    X11Window::~X11Window()
    {
        Shutdown();
    }

    void X11Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void X11Window::Init(const WindowProps &props)
    {
        m_Data.Width = props.Width, m_Data.Height = props.Height, m_Data.Title = props.Title;

        if (!s_GLFWInitialized)
        {
            if(!glfwInit())
                std::cerr << "Failed to initialize GLFW!" << std::endl;
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
    }

    void X11Window::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }
}
