//
// Created by Htrap19 on 12/8/21.
//

#include "Shader.h"

#include "Freesia/Renderer/Renderer.h"

#include "Freesia/Core/Assert.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Freesia
{
    Ref<Shader> Shader::Create(const std::string& filepath)
    {
        switch (Renderer::GetApi())
        {
            case RendererAPI::Api::None: FS_CORE_ASSERT(false, "RendererAPI::Api::None is currently not supported!"); return nullptr;
            case RendererAPI::Api::OpenGL: return CreateRef<OpenGLShader>(filepath);

            default:
                break;
        }

        FS_CORE_ASSERT(false);
        return nullptr;
    }

    Ref<Shader> Shader::Create(std::string name, const std::string& vertSrc, const std::string& fragSrc)
    {
        switch (Renderer::GetApi())
        {
            case RendererAPI::Api::None: FS_CORE_ASSERT(false, "RendererAPI::Api::None is currently not supported!"); return nullptr;
            case RendererAPI::Api::OpenGL: return CreateRef<OpenGLShader>(std::move(name), vertSrc, fragSrc);

            default:
                break;
        }

        FS_CORE_ASSERT(false);
        return nullptr;
    }
}