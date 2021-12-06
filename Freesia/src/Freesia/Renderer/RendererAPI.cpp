//
// Created by Htrap19 on 12/6/21.
//

#include "RendererAPI.h"

#include "Freesia/Core/Assert.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Freesia
{
    RendererAPI::Api RendererAPI::s_Api = RendererAPI::Api::OpenGL;

    Scope<RendererAPI> RendererAPI::Create()
    {
        switch (s_Api)
        {
            case Api::None: FS_CORE_ASSERT(false, "RendererAPI::Api::None is currently not supported!"); return nullptr;
            case Api::OpenGL: return CreateScope<OpenGLRendererAPI>();

            default:
                break;
        }

        FS_CORE_ASSERT(false);
        return nullptr;
    }
}