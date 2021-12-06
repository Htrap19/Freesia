//
// Created by Htrap19 on 12/6/21.
//

#ifndef FREESIA_OPENGLRENDERERAPI_H
#define FREESIA_OPENGLRENDERERAPI_H

#include "Freesia/Renderer/RendererAPI.h"

namespace Freesia
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void Init() override;
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        void Clear() override;
        void SetClearColor(const glm::vec4 &color) override;
    };
}

#endif //FREESIA_OPENGLRENDERERAPI_H
