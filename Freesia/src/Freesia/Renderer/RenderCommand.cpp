//
// Created by Htrap19 on 12/6/21.
//

#include "RenderCommand.h"

namespace Freesia
{
    Scope<RendererAPI> RenderCommand::s_RendererApi = RendererAPI::Create();
}