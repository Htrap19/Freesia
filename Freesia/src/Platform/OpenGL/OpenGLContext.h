//
// Created by Htrap19 on 12/4/21.
//

#ifndef FREESIA_OPENGLCONTEXT_H
#define FREESIA_OPENGLCONTEXT_H

#include "Freesia/Renderer/GraphicsContext.h"

namespace Freesia
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        explicit OpenGLContext(GLFWwindow* window);

        void Init() override;
        void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };
}

#endif //FREESIA_OPENGLCONTEXT_H
