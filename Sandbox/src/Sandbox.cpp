//
// Created by Htrap19 on 12/6/21.
//

#include "Sandbox.h"

Sandbox::Sandbox()
    : Freesia::Layer("Sandbox")
{
}

void Sandbox::OnAttach()
{
}

void Sandbox::OnUpdate(Freesia::TimeStep ts)
{
    Freesia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Freesia::RenderCommand::Clear();
}
