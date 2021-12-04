//
// Created by Htrap19 on 12/4/21.
//

#include "GraphicsContext.h"
#include <GLFW/glfw3.h>

#include "Platform/OpenGL/OpenGLContext.h"

namespace Freesia
{
    Scope<GraphicsContext> GraphicsContext::Create(GLFWwindow* window)
    {
        return CreateScope<OpenGLContext>(window);
    }
}