//
// Created by htrap19 on 12/15/21.
//

#include "FrameBuffer.h"

#include "Freesia/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Freesia
{
    Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
    {
        switch (Renderer::GetApi())
        {
            case RendererAPI::Api::None: FS_CORE_ASSERT(false, "RendererAPI::Api::None is currently not supported!"); return nullptr;
            case RendererAPI::Api::OpenGL: return CreateRef<OpenGLFrameBuffer>(spec);

            default:
                break;
        }

        FS_CORE_ASSERT(false);
        return nullptr;
    }
}