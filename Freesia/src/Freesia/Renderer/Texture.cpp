//
// Created by Htrap19 on 12/10/21.
//

#include "Texture.h"

#include "Freesia/Renderer/Renderer.h"

#include "Freesia/Core/Assert.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Freesia
{
    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetApi())
        {
            case RendererAPI::Api::None: FS_CORE_ASSERT(false, "RendererAPI::Api::None is currently not supported!"); return nullptr;
            case RendererAPI::Api::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);

            default:
                break;
        }

        FS_CORE_ASSERT(false);
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::string& path, bool flip)
    {
        switch (Renderer::GetApi())
        {
            case RendererAPI::Api::None: FS_CORE_ASSERT(false, "RendererAPI::Api::None is currently not supported!"); return nullptr;
            case RendererAPI::Api::OpenGL: return CreateRef<OpenGLTexture2D>(path, flip);

            default:
                break;
        }

        FS_CORE_ASSERT(false);
        return nullptr;
    }
}