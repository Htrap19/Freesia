//
// Created by Htrap19 on 12/6/21.
//

#ifndef FREESIA_RENDERERAPI_H
#define FREESIA_RENDERERAPI_H

#include <glm/glm.hpp>

#include "Freesia/Core/Core.h"

namespace Freesia
{
    class RendererAPI
    {
    public:
        enum class Api
        {
            None = 0, OpenGL = 1
        };

    public:
        virtual ~RendererAPI() = default;

        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;

        static inline Api GetApi() { return s_Api; }
        static Scope<RendererAPI> Create();
    private:
        static Api s_Api;
    };
}

#endif //FREESIA_RENDERERAPI_H
