//
// Created by Htrap19 on 12/4/21.
//

#ifndef FREESIA_GRAPHICSCONTEXT_H
#define FREESIA_GRAPHICSCONTEXT_H

#include "Freesia/Core/Core.h"

struct GLFWwindow;

namespace Freesia
{
    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        static Scope<GraphicsContext> Create(GLFWwindow* window);
    };
}

#endif //FREESIA_GRAPHICSCONTEXT_H
