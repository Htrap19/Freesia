//
// Created by Htrap19 on 12/1/21.
//

#include "X11Window.h"
#include "GLFW/glfw3.h"

#include "Freesia/Core/Log.h"
#include "Freesia/Events/WindowEvent.h"
#include "Freesia/Events/KeyEvent.h"
#include "Freesia/Events/MouseEvent.h"

namespace Freesia
{
    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description)
    {
        FS_CORE_ERROR("GLFWError[{0}]: {1}", error, description);
    }

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

        FS_CORE_INFO("Creating Window '{0}' ({1}, {2})", props.Title, props.Width, props.Height);

        if (s_GLFWWindowCount == 0)
        {
            if(!glfwInit())
                FS_CORE_ERROR("Failed to initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        s_GLFWWindowCount++;

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            auto& data = *(WindowData*) glfwGetWindowUserPointer(window);
            data.Width = (uint32_t)width;
            data.Height = (uint32_t)height;

            WindowResizedEvent e(width, height);
            data.EventCallback(e);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            auto& data = *(WindowData*) glfwGetWindowUserPointer(window);

            WindowClosedEvent e;
            data.EventCallback(e);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            auto& data = *(WindowData*) glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent e((KeyCode)key, 0);
                    data.EventCallback(e);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent e((KeyCode)key);
                    data.EventCallback(e);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent e((KeyCode)key, 1);
                    data.EventCallback(e);
                    break;
                }

                default:
                    break;
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int key)
        {
            auto& data = *(WindowData*) glfwGetWindowUserPointer(window);

            KeyTypedEvent e(key);
            data.EventCallback(e);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            auto& data = *(WindowData*) glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent e((MouseCode)button);
                    data.EventCallback(e);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent e((MouseCode)button);
                    data.EventCallback(e);
                    break;
                }

                default:
                    break;
            }
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
        {
            auto data = *(WindowData*) glfwGetWindowUserPointer(window);

            MouseMovedEvent e((float)xpos, (float)ypos);
            data.EventCallback(e);
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            auto data = *(WindowData*) glfwGetWindowUserPointer(window);

            MouseScrolledEvent e((float)xOffset, (float)yOffset);
            data.EventCallback(e);
        });
    }

    void X11Window::Shutdown()
    {
        glfwDestroyWindow(m_Window);
        s_GLFWWindowCount--;
    }

}
