//
// Created by Htrap19 on 12/4/21.
//

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>

namespace Freesia
{
    OpenGLContext::OpenGLContext(GLFWwindow *window)
        : m_WindowHandle(window)
    {}

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_WindowHandle);
    }
}