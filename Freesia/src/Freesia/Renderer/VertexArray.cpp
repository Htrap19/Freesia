//
// Created by Htrap19 on 12/8/21.
//

#include "VertexArray.h"

#include "Freesia/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Freesia
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetApi())
        {
            case RendererAPI::Api::None: FS_CORE_ASSERT(false, "RendererAPI::Api::None is currently not supported!"); return nullptr;
            case RendererAPI::Api::OpenGL: return CreateRef<OpenGLVertexArray>();

            default:
                break;
        }

        FS_CORE_ASSERT(false);
        return nullptr;
    }
}