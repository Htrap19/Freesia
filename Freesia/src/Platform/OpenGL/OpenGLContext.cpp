//
// Created by Htrap19 on 12/4/21.
//

#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Freesia/Core/Assert.h"

namespace Freesia
{
    OpenGLContext::OpenGLContext(GLFWwindow *window)
        : m_WindowHandle(window)
    {}

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        FS_CORE_ASSERT(success, "Failed to initialize Glad!");

        FS_CORE_INFO("OpenGL Info:");
        FS_CORE_INFO("\tVendor  : {0}", glGetString(GL_VENDOR));
        FS_CORE_INFO("\tRenderer: {0}", glGetString(GL_RENDERER));
        FS_CORE_INFO("\tVersion : {0}", glGetString(GL_VERSION));

        FS_CORE_ASSERT(GLVersion.major > 3 || (GLVersion.major == 3 && GLVersion.minor >= 3), "Minimum required Opengl version 3.3!");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_WindowHandle);
    }
}