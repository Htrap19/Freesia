//
// Created by Htrap19 on 12/7/21.
//

#include "Buffer.h"

#include "Freesia/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Freesia
{
    // ===============================================================================================
    // Vertex Buffer =================================================================================
    // ===============================================================================================

    Ref<VertexBuffer> VertexBuffer::Create(size_t size)
    {
        switch (Renderer::GetApi())
        {
            case RendererAPI::Api::None: FS_CORE_ASSERT(false, "RendererAPI::Api::None is currently not supported!"); return nullptr;
            case RendererAPI::Api::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);

            default:
                break;
        }

        FS_CORE_ASSERT(false);
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, size_t size)
    {
        switch (Renderer::GetApi())
        {
            case RendererAPI::Api::None: FS_CORE_ASSERT(false, "RendererAPI::Api::None is currently not supported!"); return nullptr;
            case RendererAPI::Api::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);

            default:
                break;
        }

        FS_CORE_ASSERT(false);
        return nullptr;
    }

    // ===============================================================================================
    // Index Buffer ==================================================================================
    // ===============================================================================================

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t count)
    {
        switch (Renderer::GetApi())
        {
            case RendererAPI::Api::None: FS_CORE_ASSERT(false, "RendererAPI::Api::None is currently not supported!"); return nullptr;
            case RendererAPI::Api::OpenGL: return CreateRef<OpenGLIndexBuffer>(count);

            default:
                break;
        }

        FS_CORE_ASSERT(false);
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetApi())
        {
            case RendererAPI::Api::None: FS_CORE_ASSERT(false, "RendererAPI::Api::None is currently not supported!"); return nullptr;
            case RendererAPI::Api::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);

            default:
                break;
        }

        FS_CORE_ASSERT(false);
        return nullptr;
    }
}