//
// Created by Htrap19 on 12/6/21.
//

#ifndef FREESIA_RENDERER_H
#define FREESIA_RENDERER_H

#include "Freesia/Renderer/RenderCommand.h"

namespace Freesia
{
    class Renderer
    {
    public:
        static inline void Init() { RenderCommand::Init(); }
        static inline void Shutdown() {}
        static inline void OnWindowResize(uint32_t width, uint32_t height) { RenderCommand::SetViewport(0, 0, width, height); }

        static inline RendererAPI::Api GetApi() { return RendererAPI::GetApi(); }
    };
}

#endif //FREESIA_RENDERER_H
