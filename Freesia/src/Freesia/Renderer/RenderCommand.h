//
// Created by Htrap19 on 12/6/21.
//

#ifndef FREESIA_RENDERCOMMAND_H
#define FREESIA_RENDERCOMMAND_H

#include "Freesia/Renderer/RendererAPI.h"

namespace Freesia
{
    class RenderCommand
    {
    public:
        static inline void Init() { s_RendererApi->Init(); }
        static inline void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RendererApi->SetViewport(x, y, width, height); }
        static inline void Clear() { s_RendererApi->Clear(); }
        static inline void SetClearColor(const glm::vec4& color) { s_RendererApi->SetClearColor(color); }
        static inline void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) { s_RendererApi->DrawIndexed(vertexArray, indexCount); }

    private:
        static Scope<RendererAPI> s_RendererApi;
    };
}

#endif //FREESIA_RENDERCOMMAND_H
